#ifndef _M_LINKED_LIST_H_
#define _M_LINKED_LIST_H_
#include "../util.h"

typedef enum {
    L_CHAR = 1, L_SHORT = 2, L_INT = 4, L_LONG = 8, L_FLOAT = 4, L_DOUBLE = 8, L_STRING, L_STRUCT
} Type;

typedef enum {
    LLIST_OK, LLIST_ERROR
} LLIST_CODE;

typedef struct ldata {
    pointer data;
    struct ldata *prev;
    struct ldata *next;
}Ldata;

typedef struct {
    Ldata *head;
    Ldata *tail;
    u32 size;
    Type type;
} LinkedList;

typedef struct {
    pointer data;
    Ldata *llist_data;
    LinkedList *llist;
}Literator;

LinkedList *LList_create(Type type);
//append value in teil of LinkedList, if type == L_STRUCT need to set @param size, size of
//struct in bytes
LLIST_CODE LList_append_next(LinkedList *llist, void *data, u32 size);
//append value in head of LinkedList, if type == L_STRUCT need to set @param
//size, size of struct in bytes
LLIST_CODE LLIst_append_next(LinkedList *llist, void *data, u32 size);
//append value in spesial position (@param pos) in LinkedList,
//if type == L_STRUCT need tot set @param size, size of struct in bytes
LLIST_CODE LList_append_pos(LinkedList *llist, void *data, u32 size, u32 pos);
//remove item (@param data) from LinkedList, if data == NULL, remove data from
//LinkedList by Literator *p;
LLIST_CODE LList_remove(LinkedList *llist, Literator *p);
//remove item from LinkedList by @param pos
LLIST_CODE LList_remove_pos(LinkedList *llist, u32 pos);
//return Literator (void *) on first element in LinkedList 
Literator *LList_get_iterator(LinkedList *llist);
//return pointer on next element in LinkedList
void LList_iterator_next(Literator *p);
//return pointer on previous element in LinkedList
void Llist_iterator_prev(Literator *p);
//frees all memory allocated for LinkedList
LLIST_CODE LList_destroy_list(LinkedList *llist, void (*struct_free)(pointer));

#endif //_M_LINKED_LIST_H_
