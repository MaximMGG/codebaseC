#include "m_string.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

STR_ERR STR_ERROR;
#define SIZE_LEN_INFO 4
#define STR_ERR(a)  fprintf(stderr, "File - %s, func - %s, line - %d, msg - %s", __FILE__, __FUNCTION__, __LINE__, a)
#define foreach(s)  char c = *(s->str);                                      \
                    for (int i = 0; ; c = *(s->str + i), i++)                \


enum errors{
    CONCAT_ERR,
    MEM_ALLOC_ERR
};


str *newstr(const char *s) {
    str *new = (str *) malloc(sizeof(str));
    new->len = strlen(s);
    char *temp = (char *) malloc(sizeof(char) * new->len + 1 + SIZE_LEN_INFO);
    unsigned int *len_info = (unsigned int *) temp;
    *len_info = new->len;
    new->str = (temp + 4);
    strcpy(new->str, s);
    return new;
}

str newstr_local(const char *s) {
    str new = {.len = strlen(s)};
    char *temp = (char *) malloc(sizeof(char) * new.len + 1);
    unsigned int *len_info = (unsigned int *) temp;
    *len_info = new.len;
    new.str = (temp + 4);
    strcpy(new.str, s);
    return new;
}

str *newstr_val(str *d, char *value) {
    if (value == NULL) {
        STR_ERR("value is NULL");
        return NULL;
    }
    if (d->str != NULL) {
        free(d->str);
    }

    d->len = strlen(value);
    d->str = (char *) malloc(sizeof(char) * d->len + 1);
    strcpy(d->str, value);
    unsigned int *len_info = (unsigned int *) (d->str - 4);
    *len_info = d->len;

    return d;
}

//concatinate two string and return string d
str *str_concat(str *d, str *s) {
    char buf[d->len + s->len + 1];

    int j = 0;
    for(int i = 0; i < d->len; i++) {
        buf[j++] = d->str[i];
    }
    for(int i = 0; i < s->len; i++) {
        buf[j++] = s->str[i];
    }
    buf[j] = '\0';
    d = newstr_val(d, buf);

    return d;
}
//formatting string with fmt format
// str *str_format(str *d, str *fmt, ...);


List *str_split(str *d, char symbol) {
    List *list = list_create(0, l_string);
    char buf[d->len];
    int j = 0;

    foreach(d) {
        if (c == symbol) {
            buf[j] = '\0';
            list_add(list, buf);
            j = 0;
            continue;
        }
        if (c == '\0' || c == '\n') {
            buf[j] = '\0';
            list_add(list, buf);
            break;
        }
        buf[j] = c;
    }
    return list;
}
//return copy of str
str *str_copy(str *d) {
   return newstr(d->str);
}
//remove all symbols from string
str *str_remove_all(str *d, char symbol) {
    char buf[d->len];
    foreach(d) {
        if (c != symbol) {
            buf[i] = c;
        } else {
            continue;
        }
        if (c == '\0' || c == '\n') {
            buf[i] = '\0';
            break;
        }
    }
    return newstr_val(d, buf);
}
//return 1 if string d starts with "pattern"
//f.e. str *d = "hello", if pattern "he" -> return 1, 
//if pattern "qu" -> return 0
char str_starts_with(str *d, char *pattern) {

    int plen = strlen(pattern);
    for(int i = 0; i < plen; i++) {
        if (d->str[i] != pattern[i]) {
            return 0;
        }
    }
    return 1;
}
//free memory
void str_free(str *s) {
    if (s != NULL) {
        char *temp = (s->str - SIZE_LEN_INFO);
        if (s->str != NULL) {
            free(temp);
            s->str = NULL;
            s->len = 0;
        }
        free(s);
        s = NULL;
    } 
}

static void str_format_insert(str *d, char *data, int pos, int dlen) {
    char buf[d->len + dlen + 1];

    int bi = 0;
    int di = 0;

    for( ; di < pos; di++, bi++) {
        buf[bi] = d->str[di];
    }

    for(int i = 0; i < dlen; i++, bi++) {
        buf[bi] = data[i];
    }

    if (d->str[di] == '%') {
        di++;
        if (d->str[di] == 'l') {
            di += 2;
        } else {
            di++;
        }
    }

    for( ; d->str[di] != '\0'; di++, bi++) {
        buf[bi] = d->str[di];
    }
    buf[bi] = '\0';

    d = newstr_val(d, buf);
}


str *str_format(str *d, str *fmt, ...) {
    va_list li;
    va_start(li, fmt);
    char buf[200];
    if (d == NULL) d = newstr(fmt->str);

    for(int i = 0; i < d->len; i++) {
        if (d->str[i] == '%') {
            switch (d->str[i + 1]) {
                case 'd': {
                    snprintf(buf, 200, "%d", va_arg(li, int));
                } break;
                case 'f': {
                    snprintf(buf, 200, "%f", va_arg(li, double));
                } break;
                case 'c': {
                    buf[0] = (char) va_arg(li, int);
                    buf[1] = '\0';
                } break;
                case 'x': {
                    snprintf(buf, 200, "%x", va_arg(li, int));
                } break;
                case 's': {
                    snprintf(buf, 200, "%s", va_arg(li, char *));
                } break;
                case 'l': {
                    if (d->str[i + 2] == 'd') {
                        snprintf(buf, 200, "%ld", va_arg(li, long));
                    } else if(d->str[i + 2] == 'f') {
                        snprintf(buf, 200, "%lf", va_arg(li, double));
                    }
                } break;
            }
            int buf_len = strlen(buf);
            str_format_insert(d, buf, i++, buf_len);
            i += buf_len - 1;
        }
    }

    va_end(li);

    return d;
}

char str_end_with(str *d, char *pattern) {
    int iter = strlen(pattern) - 1;
    for(int i = iter, j = d->len - 1; i >= 0; i--, j--) {
        if (d->str[j] != pattern[i]) return 0;
    }
    return 1;
}

str *str_append(str *d, char *value) {
    int vlen = strlen(value);
    unsigned int *len_info = (unsigned int *) (d->str - SIZE_LEN_INFO);
    char *temp = d->str - SIZE_LEN_INFO;
    if (*len_info == d->len || *len_info <= d->len + vlen) {
        temp = (char *) realloc(temp, sizeof(char) * (d->len * 2 + vlen + 1));
        *len_info = d->len * 2 + vlen + 1;
        d->str = (temp + SIZE_LEN_INFO);
    } else {
    }
    strcpy(&d->str[d->len], value);
    d->len += vlen;
    return d;
}

void str_free_l(str *__restrict s) {
    char *temp = (s->str - SIZE_LEN_INFO);
    if (temp != NULL && s->str != NULL) {
        free(temp);
        temp = NULL;
        s->str = NULL;
    }
    s->len = 0;
}

boolean str_compare(str *a, str *b) {
    return strcmp(a->str, b->str) == 0;
}
