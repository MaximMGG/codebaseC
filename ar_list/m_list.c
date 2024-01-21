#include "m_list.h"
#include <stdlib.h>
#include <threads.h>
#include <stdio.h>
#include <string.h>

#define LIST_STANDARD_LEN 20

#define Generic_add(l)  switch(l->type) {                                                       \
                            case M_CHAR:                                                        \
                                list_add_mchar(l->list, (char *)l->val);                        \
                                break;                                                          \
                            case M_SHORT:                                                       \
                                list_add_mshort(l->list, (short *)l->val);                      \
                                break;                                                          \
                            case M_CHAR:                                                        \
                                list_add_mint(l->list, (int *)l->val);                          \
                                break;                                                          \
                            case M_CHAR:                                                        \
                                list_add_mlong(l->list, (long *)l->val);                        \
                                break;                                                          \
                            case M_CHAR:                                                        \
                                list_add_mfloat(l->list, (float *)l->val);                      \
                                break;                                                          \
                            case M_CHAR:                                                        \
                                list_add_mdouble(l->list, (double *)l->val);                    \
                                break;                                                          \
                            case M_CHAR:                                                        \
                                list_add_mstring(l->list, (char *)l->val);                      \
                                break;                                                          \
                            case M_CHAR:                                                        \
                                list_add_mstruct(l->list, l->val);                              \
                                break;                                                          \
                        }



static int list_add_mchar(List *list, char *ch){return 0;}
static int list_add_mshort(List *list, short *sh){return 0;}
static int list_add_mint(List *list, int *in){return 0;}
static int list_add_mlong(List *list, long *lo){return 0;}
static int list_add_mfloat(List *list, float *fl){return 0;}
static int list_add_mdouble(List *list, double *du){return 0;}
static int list_add_mstring(List *list, char *str){return 0;}
static int list_add_mstruct(List *list, void *struc, int size_of_struct){return 0;}





List *list_create(unsigned int len, VAL_TYPE type) {
    List *list = (List *) malloc(sizeof(List *));
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
        }
        if (sourse[i] == '\0') {
            break;
        }
        buf[j] = sourse[i];
    }
    return p_list;
}

List *list_create_from_string(const char *sourse, VAL_TYPE type) {
    int size = 0;
    char **parse_value = parse_values_from_string(sourse, &size);
    List *list = (List *) malloc(sizeof(List *));
    list->len = size;
    list->max_len = LIST_STANDARD_LEN > size ? LIST_STANDARD_LEN : size;
    list->type = type;
    list->list = (void **) malloc(sizeof(void *) * list->max_len);

    for(int i = 0; i < size; i++) {
        
    }

    return list;
}
List *list_create_from_array(void **sourse, VAL_TYPE type, int size);
List *list_set_concurrency(List *list, boolean concurrensy);










List *list_add(List *list, void *value);
List *list_add_list(List *__restrict sourse, List *dest);
List *list_contein(List *list, void *value);
List *list_remove(List *list, void *value);
void list_free_all(List *list);
