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

int str_find_last(STR d, const char *p) {
    u32 p_len = strlen(p);
    char find = 0;

    for(int i = STRLEN(d); i > 0; i--) {
        if (d[i] == p[p_len - 1]) {
            find = 1;
            for(int j = p_len - 1; j > 0; j--, i--) {
                if (d[i] != p[j]) {
                    find = 0;
                    break;
                }
            }
            if (find == 1) {
                return i + 1;
            }
        }
    }
    return -1;
}

STR str_remove_first(STR d, const char *pattern, int *index) {
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

STR str_remove_last(STR d, const char *pattern, int *index) {
    u32 p_len = strlen(pattern);
    *index = str_find_last(d, pattern);

    if (*index == -1) {
        return NULL;
    }

    char *temp = (char *) malloc(sizeof(char) * (STRLEN(d) + p_len + 1));
    strncpy(temp, d, *index);
    strcpy((temp + *index), (d + *index + p_len));

    STR t = newstr(temp);
    free(temp);
    return t;
}

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

    d = newstr(fmt);

    for(int i = 0; i < STRLEN(d); i++) {
        if (d[i] == '%') {
            switch (d[i + 1]) {
                case 'c': {
                    char temp[2];
                    temp[0] = (char)va_arg(li, int);
                    temp[1] = '\0';
                    STR ts = newstr(temp);
                    d = str_remove_first(d, "%c", &i);
                    d = str_insert(d, ts, i);
                    i += STRLEN(ts);
                    str_free(ts);
                } break;
                case 's': {
                    char *temp = va_arg(li, char *);
                    STR ts = newstr(temp);
                    d = str_remove_first(d, "%s", &i);
                    d = str_insert(d, ts, i);
                    i += STRLEN(ts);
                    str_free(ts);
                } break;
                case 'd': {
                    char temp[32] = {0}; 
                    int ti = va_arg(li, int);
                    snprintf(temp, 32, "%d", ti);
                    STR ts = newstr(temp);
                    d = str_remove_first(d, "%d", &i);
                    d = str_insert(d, ts, i);
                    i += STRLEN(ts);
                    str_free(ts);
                } break;
                case 'f': {
                    char temp[32] = {0}; 
                    float tf = (float)va_arg(li, double);
                    snprintf(temp, 32, "%f", tf);
                    STR ts = newstr(temp);
                    d = str_remove_first(d, "%f", &i);
                    d = str_insert(d, ts, i);
                    i += STRLEN(ts);
                    str_free(ts);
                } break;
                case 'u': {
                    char temp[32] = {0}; 
                    u32 tu = (u32) va_arg(li, u32);
                    snprintf(temp, 32, "%u", tu);
                    STR ts = newstr(temp);
                    d = str_remove_first(d, "%u", &i);
                    d = str_insert(d, ts, i);
                    i += STRLEN(ts);
                    str_free(ts);
                } break;
                case 'l': {
                    if (d[i + 2] == 'd') {
                        char temp[32] = {0}; 
                        i64 tld = (i64) va_arg(li, i64);
                        snprintf(temp, 32, "%ld", tld);
                        STR ts = newstr(temp);
                        d = str_remove_first(d, "%ld", &i);
                        d = str_insert(d, ts, i);
                        i += STRLEN(ts);
                        str_free(ts);
                    } else if (d[i + 2] == 'f') {
                        char temp[32] = {0}; 
                        double td = (double) va_arg(li, double);
                        snprintf(temp, 32, "%lf", td);
                        STR ts = newstr(temp);
                        d = str_remove_first(d, "%lf", &i);
                        d = str_insert(d, ts, i);
                        i += STRLEN(ts);
                        str_free(ts);
                    }
                } break;
            }
        }

    }
    va_end(li);
    return d;
}

void str_free(STR d) {
    if (d != NULL) {
        void *source = (d - ALLOC_LEN);
        if (source != NULL)
            free(source);
    }
}


STR str_copy(STR d) {
    return newstr(d);
}

STR str_remove_all(STR d, char symbol) {
    char temp[STRLEN(d)] = {};

    for(int i = 0, j = 0; i < STRLEN(d); i++) {
        if (d[i] != symbol) {
            temp[j++] = d[i];
        } 
    }
    str_free(d);
    return newstr(d);
}

boolean str_starts_with(STR d, char *pattern) {
    u32 p_len = strlen(pattern);

    for(int i = 0; i < p_len; i++) {
        if (d[i] != pattern[i]) {
            return false;
        }
    }
    return true;
}

boolean str_end_with(STR d, char *pattern) {
    u32 p_len = strlen(pattern);
    u32 d_len = STRLEN(d);

    for(int i = p_len - 1, j = d_len - 1; i > 0; i--) {
        if (d[j] != pattern[i]) {
            return false;
        }
    }
    return true;
}

STR str_append(STR d, char *value, unsigned int value_len) {
    u32 v_len = 0;
    if (value_len == 0) {
        v_len = strlen(value);
    } else {
        v_len = value_len;
    }
    byte *s = (d - ALLOC_LEN);
    u32 d_len = STRLEN(d);

    u32 *alloc_len = (u32 *)(d - ALLOC_LEN);
    if (*alloc_len == d_len || *alloc_len <= v_len + d_len) {
        s = (byte *) realloc(s, sizeof(char) * (d_len * 2 + v_len + ALLOC_LEN + 1));
        alloc_len = (u32 *) s;
        *alloc_len = d_len * 2 + v_len;
        u32 *temp_len = (u32 *)(s + LEN); 
        *temp_len = d_len;
    } else {
    }

    strcpy((d + d_len), value);

    return d;
}

boolean str_compare(STR a, STR b) {
    return (strcmp(a, b) == 0);
}
