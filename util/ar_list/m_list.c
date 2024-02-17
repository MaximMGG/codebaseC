#include "m_list.h"
#include <stdlib.h>
#include <threads.h>
#include <stdio.h>
#include <string.h>

#define LIST_STANDARD_LEN 20

#define Generic_add(l, v)  switch(l->type) {                                                    \
                            case M_CHAR:                                                        \
                                list_add_mchar(l, (char *)v);                                   \
                                break;                                                          \
                            case M_SHORT:                                                       \
                                list_add_mshort(l, (short *)v);                                 \
                                break;                                                          \
                            case M_INT:                                                         \
                                list_add_mint(l, (int *)v);                                     \
                                break;                                                          \
                            case M_LONG:                                                        \
                                list_add_mlong(l, (long *)v);                                   \
                                break;                                                          \
                            case M_FLOAT:                                                       \
                                list_add_mfloat(l, (float *)v);                                 \
                                break;                                                          \
                            case M_DOUBLE:                                                      \
                                list_add_mdouble(l, (double *)v);                               \
                                break;                                                          \
                            case M_STRING:                                                      \
                                list_add_mstring(l, (char *)v);                                 \
                                break;                                                          \
                            case M_STRUCT:                                                      \
                                list_add_mstruct(l, v);                                         \
                                break;                                                          \
                        }

#define CHECK(l) if(list_check(l)) return 1
#define FOR_L(l) for(int i = 0; i < l->len; i++)

static int list_check(List *list) {
    if (list->len >= list->max_len) {
        list->max_len <<= 1;
        list->list = realloc(list->list, sizeof(void *) * list->max_len);
    }
    return 1;
}

static int list_add_mchar(List *list, char *ch){
    char *temp = (char *) malloc(sizeof(char));
    *temp = *ch;
    list->list[list->len++] = temp;
    CHECK(list);
    return 0;
}

static int list_add_mshort(List *list, short *sh){
    short *temp = (short *) malloc(sizeof(short));
    *temp = *sh;
    list->list[list->len++] = temp;
    CHECK(list);
    return 0;
}

static int list_add_mint(List *list, int *in){
    int *temp = (int *) malloc(sizeof(int));
    *temp = *in;
    list->list[list->len++] = temp;
    CHECK(list);
    return 0;
}

static int list_add_mlong(List *list, long *lo){
    long *temp = (long *) malloc(sizeof(long));
    *temp = *lo;
    list->list[list->len++] = temp;
    CHECK(list);
    return 0;
}
static int list_add_mfloat(List *list, float *fl){
    float *temp = (float *) malloc(sizeof(float));
    *temp = *fl;
    list->list[list->len++] = temp;
    CHECK(list);
    return 0;
}
static int list_add_mdouble(List *list, double *du){
    double *temp = (double *) malloc(sizeof(double));
    *temp = *du;
    list->list[list->len++] = temp;
    CHECK(list);
    return 0;
}
static int list_add_mstring(List *list, char *str){
    char *temp = (char *) malloc(sizeof(char) * strlen(str));
    strcpy(temp, str);
    list->list[list->len++] = temp;
    CHECK(list);
    return 0;
}
static int list_add_mstruct(List *list, void *struc){
    struct temp *t = malloc(list->struct_size);
    memcpy(t, struc, list->struct_size);
    list->list[list->len++] = t;
    CHECK(list);
    return 0;
}


List *list_create(unsigned int len, VAL_TYPE type) {
    List *list = (List *) malloc(sizeof(List));
    list->len = 0;
    list->max_len = len == 0 ? LIST_STANDARD_LEN : len;
    list->type = type;
    list->list = (void **) malloc(sizeof(void *) * list->max_len);

    return list;
}

static char **parse_values_from_string(const char *sourse, int *size) {
    int parse_len = 20;
    char **p_list = (char **) malloc(sizeof(char *) * parse_len);
    int count = 0;
    char buf[128];
    for(int i = 0, j = 0; ;i++) {
        if (sourse[i] == ',') {
            buf[j] = '\0';
            p_list[count] = (char *) malloc(strlen(buf));
            strcpy(p_list[count++], buf);
            if (count == parse_len) {
                count <<= 1;
                p_list = (char **) realloc(p_list, sizeof(char *) * parse_len);
            }
            j = 0;
            continue;
        }
        if (sourse[i] == '\0') {
            buf[j] = '\0';
            p_list[count] = (char *) malloc(strlen(buf));
            strcpy(p_list[count++], buf);
            break;
        }
        if (sourse[i] == ' ') continue;
        buf[j++] = sourse[i];
    }
    *size = count;
    return p_list;
}

List *list_create_from_string(const char *sourse, VAL_TYPE type) {
    int size = 0;
    char **parse_value = parse_values_from_string(sourse, &size);
    List *list = (List *) malloc(sizeof(List));
    list->len = 0;
    list->max_len = LIST_STANDARD_LEN > size ? LIST_STANDARD_LEN : size;
    list->type = type;
    list->list = (void **) malloc(sizeof(void *) * list->max_len);
    int buf_i = 0;
    long buf_l = 0;
    double buf_d = 0.0;

    for(int i = 0; i < size; i++) {
       switch(type) {
           case M_CHAR:
               list_add_mchar(list, &parse_value[i][0]);
               break;
            case M_SHORT:
               buf_i = atoi(parse_value[i]);
               list_add_mshort(list, (short *) &buf_i);
               break;
            case M_INT:
               buf_i = atoi(parse_value[i]);
               list_add_mint(list, &buf_i);
               break;
            case M_LONG:
               buf_l = atol(parse_value[i]);
               list_add_mlong(list, &buf_l);
               break;
            case M_FLOAT:
               buf_d = atof(parse_value[i]);
               list_add_mfloat(list, (float *) &buf_d);
               break;
            case M_DOUBLE:
               buf_d = atof(parse_value[i]);
               list_add_mdouble(list, (double *) &buf_d);
               break;
            case M_STRING:
               list_add_mstring(list, parse_value[i]);
               break;
            case M_STRUCT:
               fprintf(stderr, "Error, do not work with struct");
               break;
       } 
    }

    return list;
}

List *list_create_from_array(void **sourse, VAL_TYPE type, int size) {
    List *list = (List *) malloc(sizeof(List));
    list->len = 0;
    list->max_len = size > LIST_STANDARD_LEN ? size : LIST_STANDARD_LEN;
    list->type = type;
    list->list = (void **) malloc(sizeof(void *) * list->max_len);

    int buf_i = 0;
    long buf_l = 0;
    double buf_d = 0.0;
    int i = 0;

    if (type == M_STRUCT) {
        i = 1;
    }

    for(; i < size; i++) {
       switch(type) {
           case M_CHAR:
               list_add_mchar(list, (char *)sourse[i]);
               break;
            case M_SHORT:
               buf_i = *(short *)sourse[i];
               list_add_mshort(list, (short *) &buf_i);
               break;
            case M_INT:
               buf_i = *(int *) sourse[i];
               list_add_mint(list, &buf_i);
               break;
            case M_LONG:
               buf_l = *(long *) sourse[i];
               list_add_mlong(list, &buf_l);
               break;
            case M_FLOAT:
               buf_d = *(float *) sourse[i];
               list_add_mfloat(list, (float *) &buf_d);
               break;
            case M_DOUBLE:
               buf_d = *(double *) sourse[i];
               list_add_mdouble(list, (double *) &buf_d);
               break;
            case M_STRING:
               list_add_mstring(list, (char *)sourse[i]);
               break;
            case M_STRUCT:
               list_add_mstruct(list, sourse[i]);
               break;
       } 
    }

    return list;
}
List *list_set_concurrency(List *list, boolean concurrensy) {
    list->concurrent = concurrensy;
    return list;
}


List *list_add(List *list, void *value) {
    Generic_add(list, value);
    return list;
}

List *list_add_list(List *__restrict sourse, List *dest) {
    for(int i = 0; i < dest->len; i++) {
        Generic_add(sourse, list_get(dest, i));
    }
    return sourse;
}



int list_contein(List *list, void *value) {
    int t = list->type;

#if t == M_CHAR
#define TYPE char
#elif t == M_SHORT
#define TYPE shourt
#elif t == M_INT
#define TYPE int
#elif t == M_LONG
#define TYPE long
#elif t == M_FLOAT
#define TYPE float
#elif t == M_DOUBLE
#define TYPE double
#elif t == M_STRING
#define TYPE char*
#elif t == M_STRUCT
#define TYPE void*
#endif

    FOR_L(list) {
        TYPE *v = (TYPE *) list_get(list, i);    
        if (t == M_STRING) {
            if ((strcmp((char *) value, (char *) v)) == 0) 
                return i;
        }
        if (t == M_STRUCT)
            return i;
        if (*v == *(TYPE*) value) return i;
    }

    return -1;
}

List *list_remove(List *list, void *value) {
    int pos = list_contein(list, value);
    if (pos == -1) return NULL;
    free(list->list[pos]);

    if (pos == list->len - 1) return list;
    for(int i = pos; i < list->len - 1; i++) {
        list->list[i] = list->list[i + 1];
    }
    list->len--;

    return list;
}

void *list_get(List *list, int index) {
    if (index >= list->len) {
        fprintf(stderr, "Index out of list length\n");
        return NULL;
    }
    if (index < 0) {
        fprintf(stderr, "Index less then 0\n");
        return NULL;
    }
    return list->list[index];
}

void list_free_all(List *list) {
    FOR_L(list) {
        free(list->list[i]);
    }
    free(list->list);
    list->list = NULL;
    free(list);
    list = NULL;
}

