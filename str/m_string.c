#include "m_string.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

STR_ERR STR_ERROR;

enum errors{
    CONCAT_ERR,
    MEM_ALLOC_ERR
};

str str_concat(str d, str s) {
    int d_len = strlen(d.str);
    int s_len = strlen(s.str);
    
    char *temp = (char *) malloc(d_len + s_len - 1);
    if (temp == NULL) {
        STR_ERROR = MEM_ALLOC_ERR;
    }
    memcpy(temp, d.str, d_len);
    memcpy(temp + d_len, s.str, s_len);

    int total_len = strlen(temp);
    if (total_len != d_len + s_len) {
        STR_ERROR = CONCAT_ERR;
    }
    d.str = temp;
    d.len = s_len;

    return d;
}


static str str_format_insert(str dest, void *buf) {
    char buf_s[1024];
    int copy = 1;
    for(int i = 0, j = 0; ; i++) {
        if (dest.str[i] == '\0') {
            buf_s[j] = '\0';
            break;
        }
        if (dest.str[i] == '%' && copy == 1) {
            int len = strlen(buf);
            memcpy(&buf_s[i], buf, len);
            i++;
            if (dest.str[i] == 'l') i += 2;
            else i++; 
            j += len;
            copy = 0;
        }
        buf_s[j++] = dest.str[i];
    }
    str res = STR(buf_s, res);
    return res;
}

str str_format(str s, str fmt, ...) {
    va_list li;
    va_start(li, fmt);
    s.str = fmt.str;

    for(int i = 0; i < fmt.len; i++) {
        if (fmt.str[i] == '%') {
            switch(fmt.str[i + 1]) {
                case 'd': {
                              int temp_i = va_arg(li, int);
                              char buf[24];
                              snprintf(buf, 24, "%d", temp_i);
                              s = str_format_insert(s, (void *) buf);
                              i++;
                              break;
                          }
                case 'f': {
                              float temp_f = va_arg(li, double);
                              char buf[24];
                              snprintf(buf, 24, "%f", temp_f);
                              s = str_format_insert(s, (void *) buf);
                              i++;
                              break;
                          }
                case 'l': {
                              if (fmt.str[i + 2] == 'f') {
                                  double temp_d = va_arg(li, double);
                                  char buf[24];
                                  snprintf(buf, 24, "%lf", temp_d);
                                  s = str_format_insert(s, (void *) buf);
                                  i += 2;
                                  break;
                              } else if (fmt.str[i + 2] == 'd') {
                                  long temp_l = va_arg(li, long);
                                  char buf[24];
                                  snprintf(buf, 24, "%ld", temp_l);
                                  s = str_format_insert(s, (void *) buf);
                                  i += 2;
                                  break;
                              }
                          }
                case 'c': {
                              char temp_c = (char) va_arg(li, int);
                              char buf[24];
                              snprintf(buf, 24, "%c", temp_c);
                              s = str_format_insert(s, (void *) &temp_c);
                              i++;
                              break;
                          }
                case 's': {
                              char *temp_s = (char *) va_arg(li, char*);
                              s = str_format_insert(s, (void *) temp_s);
                              i++;
                              break;
                          }
            }
        }

    }
    s.len = strlen(s.str);
    return s;
}


str str_err() {
    str err = STR("Def err", err);
    switch (STR_ERROR) {
        case MEM_ALLOC_ERR: {
            str e = STR("Memory allocation error", e);
            err = e;
            break;
            }
        case CONCAT_ERR: {
            str e = STR("String concationation error", e);
            err = e;
            break;
            }
    }
    return err;
}

str **str_split(str d, char symbol) { 
    char buf[264];
    int size = 20;
    int count = 0;
    str **arr = (str **) malloc(sizeof(str *) * size);

    for(int i = 0; i < d.len; i++) {
        if (d.str[i] == symbol) {
            buf[i] = '\0';
            int buf_len = strlen(buf);
            arr[count] = (str *) malloc(sizeof(str));
            arr[count]->str = (char *) malloc(sizeof(char) * buf_len);
            strcpy(arr[count]->str, buf);
            arr[count++]->len = buf_len;
        }
        buf[i] = d.str[i];

        if (count == size) {
            size <<= 1;
            arr = (str **) realloc(arr, sizeof(str *) * size);
        }

    }
    return arr;
}

void str_free(str *s) {
    free(s->str);
    s->len = 0;
}
