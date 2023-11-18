#include "ar_list.h"




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

    if (list->distinct == false) {
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
    } else {
        if (al_conteins(list, value)) {
            return;
        }
    }
    list->len++;
    check_list_len(list);
}





boolean al_conteins(a_list *list, void *value) {
    if (list->data_type == STRING) {
        for(int i = 0; i < list->len; i++) {
            if (!strcmp(list->value[i], value)) {
                return true;
            }
        }
        return false;
    } else {
        boolean same = false;
        for (int i = 0; i < list->len; i++) {
            unsigned char *l_point = (unsigned char *) list->value[i];
            unsigned char *v_point = (unsigned char *) value;
            for(int j = 0; j < list->data_type; j++, l_point++, v_point++) {
                if (*l_point == *v_point) {
                    same = true;
                } else {
                    same = false;
                    break;
                }
            }
            if (same == true) return true;
        }
    }
    return false;
}




void al_delete(a_list *list, void *value, unsigned int pos) {
   list->value[pos] = NULL; 
   if (pos == list->len - 1) {
       list->len--;
       return;
   }
   for(int i = pos; i < list->len - 1; i++) {
        list->value[i] = list->value[i + 1];
   }
   list->len--;
}


void *al_get(a_list *list, void *value, unsigned int pos) {
    return NULL;
}



void al_destroy(a_list *list) {
    free(list);
}




void check_list_len(a_list *list) {
    int buf;
    if (list->len == list->max_size) {
        buf = list->max_size;
        list->max_size <<= 1;
    } else {
        return;
    }

    list->value = realloc(list->value, sizeof(void *) * list->max_size);

    if (list->data_type != STRING) {
        for(int i = buf; i < list->max_size; i++) {
            list->value[i] = malloc(list->data_type);
        }
    }
}








