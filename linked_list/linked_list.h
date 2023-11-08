#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

typedef int boolean;
#define true 1
#define false 0

typedef struct s_linked_list {
    void *value;
    struct s_linked_list *next;
} linked_list;

//create linked_list and return poiter on it
linked_list * create_linked_list();
//add value in last position in linked_list
void add(linked_list *main, void *value);
//add value in declared place in linked_list
void add_pos(linked_list *main, void *value, int pos);
//return true if value contains in linked_list, oposite false
boolean contains(linked_list *main, void *value);
//delete value in (int pos) position
void delete_value(linked_list *main, int pos);
//free all linked_list and destroy it
void destroy_linked_list(linked_list *main);
#endif //_LINKED_LIST_H_
