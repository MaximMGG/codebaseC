#include "m_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define LIST_ERROR(msg) fprintf(stderr, "%s\n", msg)
#define LIST_DEF_SIZE 20


List *list_create(unsigned int size, l_type type) {
    List *new = (List *) malloc(sizeof(List));

    switch (type) {
        case l_char:
            new->type_size = 1;
            new->type = l_char;
            break;
        case l_short:
            new->type_size = 2;
            new->type = l_short;
            break;
        case l_int:
            new->type_size = 4;
            new->type = l_int;
            break;
        case l_float:
            new->type_size = 4;
            new->type = l_float;
            break;
        case l_long:
            new->type_size = 8;
            new->type = l_long;
            break;
        case l_double:
            new->type_size = 8;
            new->type = l_double;
        case l_longdouble: 
            new->type_size = 16;
            new->type = l_longdouble;
            break;
        case l_string:
            new->type_size = 8;
            new->type = l_string;
            break;
        case l_struct:
            new->type_size = -1;
            new->type = l_struct;
            break;
    }

    new->concurrent = false;
    new->max_len = LIST_DEF_SIZE;
    new->list = (void **) malloc(sizeof(void *) * new->max_len);
    new->len = 0;

    return new;
}

static boolean list_string_start_with(const char *source, const char *pattern, int p_len) {
    for(int i = 0; i < p_len; i++) {
        if (source[i] != pattern[i]) {
            return false;
        }
    }
    return true;
}

void generic_add_from_string(List *new, char *buf) {
            switch (new->type) {
                case l_char: {
                        char temp = (char) atoi(buf);
                        list_add(new, &temp);
                        break;
                }
                case l_short: {
                        short temp = (short) atoi(buf);
                        list_add(new, &temp);
                        break;
                }
                case l_int: {
                        int temp = (int) atoi(buf);
                        list_add(new, &temp);
                        break;
                }
                case l_float : {
                        float temp = (float) atof(buf);
                        list_add(new, &temp);
                        break;
                }
                case l_long: {
                        long temp = (long) atol(buf);
                        list_add(new, &temp);
                        break;
                }
                case l_double: {
                        double temp = (double) atof(buf);
                        list_add(new, &temp);
                        break;
                }
                case l_longdouble: {
                        long double temp = (long double) atof(buf);
                        list_add(new, &temp);
                        break;
                }
                case l_string: {
                        list_add(new, buf);
                        break;
                }
                case l_struct:
                        break;
            }
}

List *list_create_from_string(const char *source, l_type type, const char *diliver) {
    if (type == l_struct) {
        LIST_ERROR("Can't create list from string with type struct");
        return NULL;
    }
    List *new = list_create(0, type);
    int s_len = strlen(source);
    int d_len = strlen(diliver);
    char buf[256];
    // char **prep_list = list_string_split(source, diliver, &l_size);
    int j = 0;
    for(int i = 0; i < s_len; i++, j++) {
        if (list_string_start_with(&source[i], diliver, d_len)) {
            buf[j] = '\0';
            generic_add_from_string(new, buf);
            j = -1;
            i += d_len - 1;
            continue;
        }
        buf[j] = source[i];
    }
    buf[j] = '\0';
    generic_add_from_string(new, buf);

    return new;
}

List *list_create_from_array(void **source, l_type type, int size) {
    List *new = list_create(0, type);

    for(int i = 0; i < size; i++) {
        list_add(new, source[i]);
    }

    return new;
}

//TODO (Maxim) need to implement this functional
List *list_set_concurrencty(List *list, boolean concurrensy) {

    return list;
}

List *list_add(List *list, void *value) {
    if (value == NULL) {
        LIST_ERROR("list_add error, value == NULL");
        return list;
    }

    if (list->type == l_string) {
        list->list[list->len] = (void *) malloc(sizeof(char) * strlen((char *) value));
        strcpy(list->list[list->len], (char *) value);
    } else {
        list->list[list->len] = (void *) malloc(list->type_size);
        memcpy(list->list[list->len], value, list->type_size);
    }
    list->len++;

    if (list->type_size == -1) {
        LIST_ERROR("You need to set struct size before adding structs in list");
        return list;
    }

    if (list->len == list->max_len) {
        list->max_len <<= 1;

        list->list = (void **) realloc(list->list, sizeof(void *) * list->max_len);
    }
    return list;
}

List *list_add_list(List *source, List *temp) {
    for(int i = 0; i < temp->len; i++) {
        list_add(source, temp->list[i]);
    }
    return source;
}

int list_contain_string(List *list, const char *value) {
    for(int i = 0; i < list->len; i++) {
        char *temp = (char *) list->list[i];
        if (strcmp(temp, value) == 0) {
            return i;
        }
    }
    return -1;
}

int list_contain(List *list, void *value) {
    boolean contain = true;
    char *vp = (char *) value;

    if (list->type == l_string) {
        return list_contain_string(list, value);
    }

    for(int i = 0; i < list->len; i++) {
        char *p = (char *) list->list[i];
        for(int j = 0; j < list->type_size; j++) {
            if (*(p + j) != *(vp + j)) {
                contain = false;
                break;
            }
        }
        if (contain == true) {
            return i;
        }
    }
    return -1;
}

List *list_remove(List *list, void *value) {
    int v_pos = list_contain(list, value);
    if (v_pos == -1) {
        LIST_ERROR("list_remove error, value do not cantain in the list");
        return list;
    }

    free(list->list[v_pos]);
    list->list[v_pos] = NULL;

    if (v_pos == list->len - 1) {
        list->len--;
        return list;
    }

    for(int i = v_pos; i < list->len - 1; i++) {
        list->list[i] = list->list[i + 1];
    }

    list->len--;
    return list;
}

void *list_get(List *list, int index) {
    if (index >= list->len || index == -1) {
        LIST_ERROR("list_get error, index out of list size");
        return NULL;
    }
    return list->list[index];
}

void list_free_all(List *list) {

    for(int i = 0; i < list->len; i++) {
        free((list->list[i]));
        list->list[i] = NULL;
    }
    free(list->list);
    list->list = NULL;
    list->len = 0;
    list->max_len = 0;
    list->type_size = 0;
    free(list);
    list = NULL;
}

