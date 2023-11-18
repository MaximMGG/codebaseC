#ifndef _AR_LIST
#define _AR_LIST
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define true 1
#define false 0
typedef char boolean;

typedef enum d_type {
    CHAR = sizeof(char), 
    SHORT = sizeof(short), 
    INT = sizeof(int), 
    LONG = sizeof(long), 
    LONG_LONG = sizeof(long long), 
    FLOAT = sizeof(float), 
    DOUBLE = sizeof(double), 
    LONG_DOUBLE = sizeof(long double),
    STRING = -1
} DATA_TYPE;

typedef struct ar_list {
    void **value;
    unsigned int len;
    unsigned int max_size;
    DATA_TYPE data_type;
    boolean distinct;
} a_list;

/*  
 *  Create array_list and return it, need to set DATA_TYPE here
 *  if distinct == true ->list can contain only not same values,
 *  if try to add same value with distinct true mode, will do nothing if 
 *  that value contains in list
*/
a_list * al_create(DATA_TYPE d_type, boolean distinct);
/*add value to list, if DATA_TYPE is diffrent then DATA_TYPE in list
 *print error("ERROR: Encorrect DATA_TYPE")
*/
void al_add(a_list *list, void *value, DATA_TYPE d_type);
//return true if list contain value or false
boolean al_conteins(a_list *list, void *value);
/*
 * Delete value in pos position
*/
void al_delete(a_list *list, void *value, unsigned int pos);
/*
 * Return value from list in pos position if list distinct 
 * just return value pos can be 0
*/
void *al_get(a_list *list, void *value, unsigned int pos);

//free memory of list
void al_destroy(a_list *list);

//check length of list, if more then list->max_size malloc new memmory
void check_list_len(a_list *list);










#endif // _AR_LIST
