#include "ar_list.h"
#include <cstdio>
#include <cstring>


a_list * al_create(DATA_TYPE d_type, boolean distinct) {
    a_list *list = malloc(sizeof(*list));
    list->data_type = d_type;
    list->distinct = distinct;
    list->max_size = 20;
    list->len = 0;

    list->value = malloc(sizeof(void *) * list->max_size);

    if (d_type != STRING) {
        for(int i = 0; i < list->max_size; i++) {
            list->value[i] = malloc(d_type); 
        }
    }
    return list;
}



void al_add(a_list *list, void *value, DATA_TYPE d_type) {
    if (list->data_type != d_type) {
        fprintf(stderr, "ERROR: Incorrect DATA_TYPE");
        return;
    }

    if (d_type == STRING) {
        list->value[list->len] = malloc(sizeof(char) * strlen((char *)value));        
        strcpy(list->value[list->len], (char *) value);
    } else {
        unsigned char *l_point = (unsigned char *) list->value[list->len];
        unsigned char *v_point = (unsigned char *) value;

        for(int i = 0; i < list->data_type; i++, l_point++, v_point++) {
            *l_point = *v_point;
        }
    }
    list->len++;
    check_list_len(list);
}





boolean al_conteins(a_list *list, void *value);




void al_delete(a_list *list, void *value, unsigned int pos);



void *al_get(a_list *list, void *value, unsigned int pos);



void al_destroy(a_list *list);




void check_list_len(a_list *list);
