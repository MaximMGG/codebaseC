#include "m_list.h"
#include <stdlib.h>
#include <threads.h>
#include <stdio.h>
#include <string.h>

#define LIST_STANDARD_LEN 20

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
        switch (type) {
            case M_CHAR:
                char v = parse_value[i][0];
                break;
            case M_SHORT:
                break;
            case M_INT:
                break;
            case M_LONG:
                break;
            case M_FLOAT:
                break;
            case M_DOUBLE:
                break;
            case M_STRING:
                break;
            case M_STRUCT:
                fprintf(stderr, "parsing error, do work with struct type");
                break;
        }
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
