#include "pr_map.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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

Property *parse_property(char *line) {
    Property *prop = malloc(sizeof(Property));
    unsigned int len = strlen(line);
    char *p = line;
    while(*p != '=') {
        p++;
    }
    prop->key = (char *) malloc(line - p + 1);
    prop->val = (char *) malloc(len - (unsigned int)(line - p));
    char *ptr = line;
    char *buf = prop->key;
    while (ptr != p) {
        *(buf++) = *(ptr++);
    }
    p++;
    *buf = '\0';
    buf = prop->val;
    while(*p != '\0') {
        *(buf++) = *(p++);
    }
    *buf = '\0';

    return prop;
}


static char *find_value_by_key(FILE *f, char *key) {
    char buf[128];
    while(!feof(f)) {
       fgets(buf, 128, f); 
       Property *prop = parse_property(buf);
       if (strcmp(prop->key, key) == 0) {
           char *res = (char *) malloc(sizeof(prop->val));
           strcpy(res, prop->val);
           freeP(prop);
           return res;
       }
       freeP(prop);
    }
    return NULL;
}

char *get_property_from_file(char *filename, char *key) {
    FILE *f;
    if (filename == NULL) {
        f = fopen(STANDARD_PROP_FILE1, "r");
        if (f == NULL) {
            f = fopen(STANDARD_PROP_FILE2, "r");
            if (f == NULL) {
                fprintf(stderr, "property.conf file does not exist\n");
            }
        }
    } else {
        f = fopen(filename, "r");
        if (f == NULL) {
            fprintf(stderr, "File %s does not exist\n", filename);
        }
    }
    
    char *val = find_value_by_key(f, key);
    if (val == NULL) {
        fprintf(stderr, "Can not find value for key %s\n", key);
    }
    fclose(f);

    return val;
}


void freeP(Property *pr) {
    free(pr->key);
    free(pr->val);
    free(pr);
}
