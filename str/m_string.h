#ifndef _M_STRING_
#define _M_STRING_
#include <string.h>

typedef struct {
    char *str;
    unsigned int len;
}str;

typedef int STR_ERR;

extern STR_ERR STR_ERROR;

#define STR(a) {a, strlen(a)}

//concatinate two string and return string d
str str_concat(str d, str s);
//formatting string with fmt format
str str_format(str d, str fmt, ...);
//return str arr split by symbol
str **str_split(str d, char symbol);
//return STR_ERR messag
str str_err();



#endif //_M_STRING_
