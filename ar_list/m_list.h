#ifndef _M_LIST_
#define _M_LIST_

#include <threads.h>

typedef char boolean;
#define true 1
#define false 0

typedef enum {
    M_CHAR,
    M_SHORT,
    M_INT,
    M_LONG,
    M_FLOAT,
    M_DOUBLE,
    M_STRING,
    M_STRUCT
} VAL_TYPE;


struct s_list {
    void **list;
    unsigned int len;
    unsigned int max_len;
    VAL_TYPE type;
    boolean concurrent;
    mtx_t lock;
};

typedef struct s_list List;

//create new list, if len = 0, set defoult length, if not, create list with lenth "len"
//return pointer to List 
List *list_create(unsigned int len, VAL_TYPE type);
/*create list from string sourse, parse all values from string to list
 * string should be like "value1, value2, value3, ..."
 * vork only with numeric types and strings
 * return pointer to List
*/
List *list_create_from_string(const char *sourse, VAL_TYPE type);
// create list from array, need to set "size" of array
// if type = M_STRUCT: sourse[0] should be int* to size of struct
List *list_create_from_array(void **sourse, VAL_TYPE type, int size);
//set concurrensy functional
List *list_set_concurrency(List *list, boolean concurrensy);
//add value in List
List *list_add(List *list, void *value);
// add to list a struct, need to set "size" of struct
List *list_add_s(List *list, void *value, int size);
//add to List all values from list dest, VAL_TYPE should be same with sourse List
List *list_add_list(List *__restrict sourse, List *dest);
//return true if List contein value
List *list_contein(List *list, void *value);
//remove from List value
List *list_remove(List *list, void *value);

//free all memory in List
void list_free_all(List *list);


#endif //_M_LIST_
