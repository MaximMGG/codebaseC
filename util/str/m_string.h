#ifndef _M_STRING_
#define _M_STRING_
// #include <string.h>
// #include <stdlib.h>

typedef struct{
    char *str;
    unsigned int len;
}str;

typedef int STR_ERR;

extern STR_ERR STR_ERROR;

#define STR(a, s) {.len = (strlen(a))};                                      \
                    s.str = (char *) malloc(sizeof(char) * strlen(a) + 1);   \
                    strcpy(s.str, a);                                        


// #define STR(a, s) (str *) malloc(sizeof(str));                                  \
//                     s->len = strlen(a); s->str = (char *) malloc(s->len);       \
//                     strcpy(s->str, a);

str *str_new_val(str *d, char *value);
//concatinate two string and return string d
str *str_concat(str *d, str *s);
//formatting string with fmt format
str *str_format(str *d, str *fmt, ...);
//return str arr split by symbol
str **str_split(str *d, char symbol, int *count);
//return STR_ERR messag
str *str_err();
//return copy of str
str *str_copy(str *d);
//remove all symbols from string
str *str_remove_all(str *d, char symbol);
//return 1 if string d starts with "pattern"
//f.e. str *d = "hello", if pattern "he" -> return 1, 
//if pattern "qu" -> return 0
char str_starts_with(str *d, char *pattern);
//free memory
void str_free(str *s);


#endif //_M_STRING_
