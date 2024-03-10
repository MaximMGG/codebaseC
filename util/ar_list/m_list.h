#ifndef _M_LIST_
#define _M_LIST_

#include <threads.h>

typedef char boolean;
#define true 1
#define false 0

typedef struct s_list {
    void **list;
    unsigned int len;
    unsigned int max_len;
    int type_size;

    boolean concurrent;
    mtx_t lock;
} List;

//create new list, if len = 0, set defoult length, if not, create list with lenth "len"
//@param type_size need to set size of data in list
//return pointer to List 
List *list_create(unsigned int len, int type_size);
/*create list from string sourse, parse all values from string to list
 * string should be like "value1, value2, value3, ..."
 * vork only with numeric types and strings
 * return pointer to List
*/
List *list_create_from_string(const char *sourse, int type_size, const char *diliver);
// create list from array, need to set "size" of array
List *list_create_from_array(void **sourse, int type_size, int size);
//set concurrensy functional
List *list_set_concurrency(List *list, boolean concurrensy);
//add value in List
List *list_add(List *list, void *value);
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


#endif //_M_LIST_
