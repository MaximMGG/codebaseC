#include "pr_map.h"
#include <stdlib.h>
#include <string.h>

#define PROPERTY_SIZE 20
#define PROP_BUFFER_SIZE 64

int pr_size = PROP_BUFFER_SIZE;


Property **parse_get_response(char *response, int *property_len) {
    Property **prop_m = (Property **)malloc(sizeof(Property *) * pr_size);
    int count = 0;
    char buf[PROP_BUFFER_SIZE];
    char *pc = response;
    char *buf_p = buf;

    while(*pc != '\0') {
        if (*pc == '"') {
            pc++;
            while (*pc != '"') {
                *(buf_p++) = *(pc++);
            }
            pc++;
            *buf_p = '\0';
            Property *tmp_prop = malloc(sizeof(Property));
            tmp_prop->key = malloc(sizeof(strlen(buf)));
            strcpy(tmp_prop->key, buf);
            buf_p = buf;
            if (*pc == ':') {
                pc++;
                if (*pc == '"') pc++;
                while(*pc != '"' && *pc != ',' && *pc != '}') {
                    *(buf_p++) = *(pc++);
                }
                *buf_p = '\0';
                tmp_prop->val = malloc(sizeof(strlen(buf)));
                strcpy(tmp_prop->val, buf);
                buf_p = buf;

                if (*pc == '"') pc++;
            }
            prop_m[count++] = tmp_prop;
            if (count == pr_size - 1) {
                pr_size <<= 1;
                prop_m = realloc(prop_m, sizeof(Property *) * pr_size);
            }
        }
        pc++;
    }
    *property_len = count;
    return prop_m;
}

void free_property(Property **y_prop, int property_len) {
    for(int i = 0; i < property_len; i++) {
        free(y_prop[i]->key);
        free(y_prop[i]->val);
        free(y_prop[i]);
    }
    free(y_prop);
}

void *set_property_in_struct_map(unsigned int size, void *y_struct, Property **pr) {
    char **buf = (char **)y_struct;

    for(int i = 0; i < size; i++) {
        buf[i] = (char *)malloc(strlen(pr[i]->val));
        strcpy(buf[i], pr[i]->val);
    }

    return y_struct;
}

void free_struct_map(void *y_struct, unsigned int size) {
    char **buf = (char **) y_struct;

    for(int i = 0; i < size; i++) {
        free(buf[i]);
    }

    free(y_struct);

}

