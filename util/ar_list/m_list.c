#include "m_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LIST_ERROR(msg) fprintf(stderr, "%s\n", msg)
#define LIST_DEF_SIZE 20


List *list_create(unsigned int size, int type_size) {
    List *new = (List *) malloc(sizeof(List));
    if (type_size == 0) {
        LIST_ERROR("type_size if 0");
        return NULL;
    }
    new->type_size = type_size;
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


List *list_create_from_string(const char *source, int type_size, const char *diliver) {
    List *new = list_create(0, type_size);
    int s_len = strlen(source);
    int d_len = strlen(diliver);
    char buf[256];
    // char **prep_list = list_string_split(source, diliver, &l_size);
    int j = 0;
    for(int i = 0; i < s_len; i++, j++) {
        if (list_string_start_with(&source[i], diliver, d_len)) {
            buf[j] = '\0';
            list_add(new, buf);
            j = -1;
            i += d_len;
            continue;
        }
        buf[j] = source[i];
    }
    buf[++j] = '\0';
    list_add(new, buf);

    return new;
}

List *list_create_from_array(void **source, int type_size, int size) {
    List *new = list_create(0, type_size);

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
    list->list[list->len] = (void *) malloc(list->type_size);
    memcpy(list->list[list->len++], value, list->type_size);

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

int list_contain(List *list, void *value) {
    boolean contain = true;
    char *vp = (char *) value;

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


