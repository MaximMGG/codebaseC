#ifndef _M_STRING_
#define _M_STRING_
// #include <string.h>
// #include <stdlib.h>
#include <util/util.h>

typedef char * STR;
#define STRLEN(s) *(unsigned int *) (s - 4)


//create new string, return pointer on str (str *) allocated memory in the heap
STR newstr(const char *s);
//do not create new string, just free d->str, and copy value to new allocated
//d->str
STR newstr_val(STR d, const char *value);
//concatinate two string and return string d
STR str_concat(STR d, STR s);

//return index where was find p (pattern) first times,
//return -1 if did't find any p in d
int str_find_first(STR d, const char *p);

//replace first matched pattern in STR d
STR str_replace_first(STR d, const char *pattern, int *index);
//replace last matched pattern in STR d
STR str_replace_last(STR d, const char *pattern);
//insert source STR into dest STR
STR str_insert(STR d, STR s, unsigned int index);
/*formatting string with fmt format
* for now only working with patterns like %d, %c, %f, %lf, %ld, %s, %x
*/
STR str_format(STR d, STR fmt, ...);
//return List split by symbol
// List *str_split(STR d, char symbol);
//return copy of str
STR str_copy(STR d);
//remove all symbols from string
STR str_remove_all(STR d, char symbol);
//return 1 if string d starts with "pattern"
//f.e. str *d = "hello", if pattern "he" -> return 1, 
//if pattern "qu" -> return 0
boolean str_starts_with(STR d, char *pattern);
// return 1 if string d ends with "pattern"
// f.e. str *d = "Hello", if pattern "llo" return 1
// if "le" return 0;
boolean str_end_with(STR d, char *pattern);
//append to str new value, if value_len == 0, append all value, if not, then
//append value_len bytes of value
STR str_append(STR d, char *value, unsigned int value_len);
//free memory
void str_free(STR __restrict s);
//compare two strings, return true is same or false;
boolean str_compare(STR a, STR b);

#endif //_M_STRING_
