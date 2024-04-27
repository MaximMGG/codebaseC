#ifndef _M_LIST_
#define _M_LIST_

#include <threads.h>

typedef char boolean;
#define true 1
#define false 0

typedef enum{
    l_char = 1, 
    l_short = 2, 
    l_int = 4, 
    l_long = 8, 
    l_float, 
    l_double, 
    l_longdouble = 16, 
    l_string = 14, 
    l_struct = -1
} l_type;

typedef struct s_list {
    void **list;
    unsigned int len;
    unsigned int max_len;
    int type_size;
    l_type type;

    boolean concurrent;
    mtx_t lock;
} List;

//create new list, if len = 0, set defoult length, if not, create list with lenth "len"
//@param type need to set type of data
//if type == l_struct need to set List->type_size = sizeof(your struct)
//return pointer to List 
List *list_create(unsigned int len, l_type type);
/*create list from string sourse, parse all values from string to list
 * string should be like "value1, value2, value3, ..."
 * vork only with numeric types and strings
 * return pointer to List
*/
List *list_create_from_string(const char *sourse, l_type size, const char *diliver);
// create list from array, need to set "size" of array
List *list_create_from_array(void **sourse, l_type type, int size);
//set concurrensy functional
List *list_set_concurrency(List *list, boolean concurrensy);
//add value in List
List *list_add(List *list, void *value);
//add string value in List
List *list_adds(List *list, char *value);
//add to List all values from list temp 
List *list_add_list(List *__restrict sourse, List *temp);
//return true if List contein value
int list_contain(List *list, void *value);
//remove from List value
List *list_remove(List *list, void *value);
//return value from List
void *list_get(List *list, int index);
//free all memory in List
void list_free_all(List *list);
//free all memory in List for l_struct
void list_free_all_struct(List *list, void (*free_func)(void *f));


#endif //_M_LIST_
