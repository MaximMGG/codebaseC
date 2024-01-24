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

str str_format(str s, str fmt, ...) {
    va_list li;
    va_start(li, fmt);
    s.str = fmt.str;

    char buf_1[1024];
    char buf_2[1024];

    for(int i = 0; i < fmt.len; i++) {
        if (fmt.str[i] == '%') {
            switch(fmt.str[i + 1]) {
                case 'd': {
                              snprintf(buf_1, 1024, s.str, (int) va_arg(li, int));
                              s.str = buf_1;
                              i++;
                              break;
                          }
                case 'f': {
                              snprintf(buf_1, 1024, s.str, (float) va_arg(li, double));
                              s.str = buf_1;
                              i++;
                              break;
                          }
                case 'l': {
                              if (fmt.str[i + 2] == 'f') {
                                  snprintf(buf_1, 1024, s.str, (double) va_arg(li, double));
                                  s.str = buf_1;
                                  i += 2;
                                  break;
                              } else if (fmt.str[i == 2] == 'd') {
                                  snprintf(buf_1, 1024, s.str, (long) va_arg(li, long));
                                  s.str = buf_1;
                                  i += 2;
                                  break;
                              }
                          }
                case 'c': {
                              snprintf(buf_1, 1024, s.str, (char) va_arg(li, int));
                              s.str = buf_1;
                              i++;
                              break;
                          }
                case 's': {
                              snprintf(buf_1, 1024, s.str, (char *) va_arg(li, char*));
                              s.str = buf_1;
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
