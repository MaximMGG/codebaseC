#include "m_string.h"
#include <string.h>
#include <stdlib.h>

#define LEN 4
#define ALLOC_LEN 8

STR newstr(const char *s) {
    unsigned int s_len = strlen(s);
    STR new =  (STR) malloc(sizeof(char) * s_len + ALLOC_LEN + 1);

    if (new == NULL) {
        return NULL;
    }

    unsigned int *new_alloc_len = (unsigned int *) new;
    unsigned int *new_len = (unsigned int *) (new + LEN);
    *new_alloc_len = *new_len = s_len;
    STR new_s = (STR) (new + ALLOC_LEN);

    strcpy(new_s, s);

    return new_s;
}

STR newstr_val(STR d, const char *value) {
    unsigned int s_len = strlen(value);
    STR new = (STR)(d - ALLOC_LEN);

    new = (STR) realloc(new, sizeof(char) * s_len + ALLOC_LEN + 1);
    if (new == NULL) {
        return NULL;
    }

    unsigned int *new_alloc_len = (unsigned int *) new;
    unsigned int *new_len = (unsigned int *) (new + LEN);
    *new_alloc_len = *new_len = s_len;
    STR new_s = (STR) (new + ALLOC_LEN);

    strcpy(new_s, value);
    return new_s;
}

STR str_concat(STR d, STR s) {
    STR new_d = (d - ALLOC_LEN);
    new_d = (STR) realloc(new_d, sizeof(char) * (STRLEN(d) + STRLEN(s)) + ALLOC_LEN + 1);
    strcpy(&d[STRLEN(d)], s);
    unsigned int *new_alloc_len = (unsigned int *) new_d;
    unsigned int *new_len = (unsigned int *) (new_d + LEN);
    *new_alloc_len = *new_len = STRLEN(d) + STRLEN(s);

    return (STR) new_d + ALLOC_LEN;
}

