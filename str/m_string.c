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

enum types {
    INT, 
    FLOAT,
    DOUBLE,
    LONG,
    CHAR,
    SHORT,
    STRING
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


static str str_format_insert(str dest, void *buf, enum types type) {
    char buf_s[1024];
}

str str_format(str s, str fmt, ...) {
    va_list li;
    va_start(li, fmt);
    s.str = fmt.str;
    str res = STR(fmt.str);

    for(int i = 0; i < fmt.len; i++) {
        if (fmt.str[i] == '%') {
            str temp = STR(&fmt.str[i]);
            switch(fmt.str[i + 1]) {
                case 'd': {
                              int temp_i = va_arg(li, int);
                              s = str_format_insert(temp, (void *) &temp_i, INT);
                              i++;
                              break;
                          }
                case 'f': {
                              float temp_f = va_arg(li, double);
                              s = str_format_insert(temp, (void *) &temp_f, FLOAT);
                              i++;
                              break;
                          }
                case 'l': {
                              if (fmt.str[i + 2] == 'f') {
                                  double temp_d = va_arg(li, double);
                                  s = str_format_insert(temp, (void *) &temp_d, DOUBLE);
                                  i += 2;
                                  break;
                              } else if (fmt.str[i == 2] == 'd') {
                                  i += 2;
                                  break;
                              }
                          }
                case 'c': {
                              i++;
                              break;
                          }
                case 's': {
                              i++;
                              break;
                          }
            }
        }

    }
    return s;
}


str str_err() {
    str err = STR("Def err");
    switch (STR_ERROR) {
        case MEM_ALLOC_ERR: {
            str e = STR("Memory allocation error");
            err = e;
            break;
            }
        case CONCAT_ERR: {
            str e = STR("String concationation error");
            err = e;
            break;
            }
    }
    return err;
}
