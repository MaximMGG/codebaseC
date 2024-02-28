#ifndef _M_STRING_
#define _M_STRING_
// #include <string.h>
// #include <stdlib.h>
#include <util/m_list.h>

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

//create new string, allocated memory 
str *newstr(char *s);
//do not create new string, just free d->str, and copy value to new allocated
//d->str
str *newstr_val(str *d, char *value);
//concatinate two string and return string d
str *str_concat(str *d, str *s);
/*formatting string with fmt format
* for now only working with patterns like %d, %c, %f, %lf, %ld, %s, %x
*/
str *str_format(str *d, str *fmt, ...);
//return List split by symbol
List *str_split(str *d, char symbol);
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

// return 1 if string d ends with "pattern"
// f.e. str *d = "Hello", if pattern "llo" return 1
// if "le" return 0;
char str_end_with(str *d, char *pattern);
//free memory
void str_free(str *__restrict s);


#endif //_M_STRING_
