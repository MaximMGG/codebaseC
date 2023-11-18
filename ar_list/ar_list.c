#include "ar_list.h"


a_list * al_create(DATA_TYPE d_type, boolean distinct) {
    a_list *list = malloc(sizeof(*list));
    list->data_type = d_type;
    list->distinct = distinct;
    list->max_size = 20;

    list->value = malloc(sizeof(void *) * list->max_size);

    if (d_type != STRING) {
        for(int i = 0; i < list->max_size; i++) {
            list->value[i] = malloc(d_type); 
        }
    }
    return list;
}



void al_add(a_list *list, void *value, DATA_TYPE);




boolean al_conteins(a_list *list, void *value);




void al_delete(a_list *list, void *value, unsigned int pos);



void *al_get(a_list *list, void *value, unsigned int pos);
