#include "m_string.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#define LEN 4
#define ALLOC_LEN 8

STR newstr(const char *s) {
    unsigned int s_len = strlen(s);
    STR new = (STR) malloc(sizeof(char) * (s_len + ALLOC_LEN + 1));

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

    if (s_len < STRLEN(d)) {
        free(new);
        new = malloc(sizeof(char) * (s_len + ALLOC_LEN + 1));
    } else {
        new = (STR) realloc(new, sizeof(char) * (s_len + ALLOC_LEN + 1));
    }

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
    u32 d_len = STRLEN(d);
    u32 s_len = STRLEN(s);

    new_d = (STR) realloc(new_d, sizeof(char) * (d_len + s_len) + ALLOC_LEN + 1);
    strcpy((new_d + ALLOC_LEN + d_len), s);
    unsigned int *new_alloc_len = (unsigned int *) new_d;
    unsigned int *new_len = (unsigned int *) (new_d + LEN);
    *new_alloc_len = *new_len = d_len + s_len;

    return (STR) new_d + ALLOC_LEN;
}

int str_find_first(STR d, const char *p) {
    int p_len = strlen(p);
    char find = 0;
    for(int i = 0; i < STRLEN(d); i++) {
        if (d[i] == p[0]) {
            for(int j = 0; j < p_len; i++, j++) {
                find = 1;
                if (d[i] != p[j]) {
                    find = 0;
                    break;
                }
            }
            if (find) {
                return i - p_len;
            }
        }
    }
    return -1;
}

STR str_replace_first(STR d, const char *pattern, int *index) {
    int p_len = strlen(pattern);
    *index = str_find_first(d, pattern);

    if (*index == -1) {
        return NULL;
    }
    char *temp = (char *) malloc(sizeof(char) * STRLEN(d) + p_len + 1);
    strncpy(temp, d, *index);
    strcpy((temp + *index), (d + *index + p_len));

    d = newstr_val(d, temp);
    free(temp);

    return d;
}

STR str_replace_last(STR d, const char *pattern);

STR str_insert(STR d, STR s, unsigned int index) {
    u32 d_len = STRLEN(d);
    u32 s_len = STRLEN(s);
    char *temp = malloc(sizeof(char) * (d_len + s_len + 1));
    strncpy(temp, d, index);
    strcpy((temp + index), s);
    strcpy((temp + index + s_len), (d + index));
    d = newstr_val(d, temp);
    free(temp);
    return d;
}


static void str_format_insert(STR d, STR s, unsigned int len) {
    int d_len = strlen(d);
    d = realloc(d, sizeof(char) * d_len + len + 1);


}


STR str_format(STR d, STR fmt, ...) {
    va_list li;
    va_start(li, fmt);

    for(int i = 0; i < STRLEN(fmt); i++) {
        if (fmt[i] == '%') {
            switch (fmt[i + 1]) {
                case 'c': {
                    STR temp = va_arg(li, char *);


                }
            }
        }

    }
    return NULL;
}
