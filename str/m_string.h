#ifndef _M_STRING_
#define _M_STRING_
#include <string.h>
#include <stdlib.h>

typedef struct{
    char *str;
    unsigned int len;
}str;

typedef int STR_ERR;

extern STR_ERR STR_ERROR;

// #define STR(a, s) {.len = (strlen(a))};                                      \
//                     s.str = (char *) malloc(sizeof(char) * strlen(a));       \
//                     strcpy(s.str, a);                                        \
//

#define STR(a, s) (str *) malloc(sizeof(str));                                  \
                    s->len = strlen(a); s->str = (char *) malloc(s->len);       \
                    strcpy(s->str, a);

//concatinate two string and return string d
str *str_concat(str *d, str *s);
//formatting string with fmt format
str *str_format(str *d, str *fmt, ...);
//return str arr split by symbol
str **str_split(str *d, char symbol);
//return STR_ERR messag
str *str_err();
//free memory
void str_free(str *s);


#endif //_M_STRING_
