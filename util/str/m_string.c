#include "m_string.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

STR_ERR STR_ERROR;
#define STR_ERR(a)  fprintf(stderr, "File - %s, func - %s, line - %d, msg - %s", __FILE__, __FUNCTION__, __LINE__, a)
#define foreach(s)  char c = *(s->str);                                      \
                    for (int i = 0; ; c = *(s->str + i), i++)                \



enum errors{
    CONCAT_ERR,
    MEM_ALLOC_ERR
};



str *newstr(char *s) {
    str *new = (str *) malloc(sizeof(str));
    new->len = strlen(s);
    new->str = (char *) malloc(sizeof(char) * new->len + 1);

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
    List *list = list_create(0, M_STRING);
    char buf[200];
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
//return STR_ERR messag
str *str_err();
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
        if (s->str != NULL) {
            free(s->str);
            s->str = NULL;
            s->len = 0;
        }
        free(s);
        s = NULL;
    } 
}
