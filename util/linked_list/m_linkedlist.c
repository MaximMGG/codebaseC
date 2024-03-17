#include "m_linkedlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

LinkedList *LList_create(Type type) {
    LinkedList *llist = (LinkedList *) malloc(sizeof(LinkedList));
    llist->size = 0;
    llist->head = NULL;
    llist->tail = NULL;
    llist->type = type;
    return llist;
}

static LLIST_CODE LList_append(LinkedList *llist, void *data, u32 size, i32 pos) {
    Ldata *ldata = (Ldata *) malloc(sizeof(Ldata));
    ldata->data = (pointer) malloc(size);
    memcpy(ldata->data, data, size);
    switch (pos) {
        case 0: {
            if (llist->size == 0) {
                llist->head = ldata;
                llist->head->next = ldata;
                llist->tail = ldata;
                llist->tail->prev = ldata;
            } else {
                ldata->next = llist->head;
                ldata->prev = NULL;
                llist->head = ldata;
            }
        } break; 
        case -1: {
            if (llist->size == 0) {
                llist->head = ldata;
                llist->head->next = ldata;
                llist->tail = ldata;
                llist->tail->prev = ldata;
            } else {
                ldata->next = NULL;
                ldata->prev = llist->tail;
                ldata->prev->next = ldata;
                llist->tail = ldata;
            }
        } break;
        default: {
            Ldata *p = llist->head;
            for(int i = 0; i < pos; i++) {
                p = p->next;
            } 
            if (p == NULL) {
                llist->head = ldata;
                llist->head->next = ldata;
                llist->tail = ldata;
                llist->tail->prev = ldata;
            } else {

            }
            ldata->prev = p->prev;
            ldata->next = p;
            p->prev = ldata;
        }
    } 
    llist->size++;
    return LLIST_OK;
}

static LLIST_CODE LList_append_helper(LinkedList *llist, void *data, u32 size, i32 pos) {
    switch(llist->type) {
        case L_CHAR:
        case L_SHORT:
        case L_INT:
        case L_LONG: {
            if (LList_append(llist, data, llist->type, pos) == LLIST_OK) {
                return LLIST_OK;
            } else {
                return LLIST_ERROR;
            }
        } break;
        case L_STRING: {
            if (LList_append(llist, data, size, pos) == LLIST_OK) {
                return LLIST_OK;
            } else {
                return LLIST_ERROR;
            }
        } break;
        case L_STRUCT: {
            if (LList_append(llist, data, size, pos) == LLIST_OK) {
                return LLIST_OK;
            } else {
                return LLIST_ERROR;
            }
        } break;
    }
    return LLIST_OK;

}

LLIST_CODE LList_append_next(LinkedList *llist, void *data, u32 size) {
    if (LList_append_helper(llist, data, size, -1) == LLIST_OK) {
        return LLIST_OK;
    } else {
        return LLIST_ERROR;
    }
}
LLIST_CODE LList_append_prev(LinkedList *llist, void *data, u32 size) {
    if (LList_append_helper(llist, data, size, 0) == LLIST_OK) {
        return LLIST_OK;
    } else {
        return LLIST_ERROR;
    }

    return LLIST_OK;
}
LLIST_CODE LList_append_pos(LinkedList *llist, void *data, u32 size, u32 pos) {
    if (LList_append_helper(llist, data, size, pos) == LLIST_OK) {
        return LLIST_OK;
    } else {
        return LLIST_ERROR;
    }
}
LLIST_CODE LList_remove(LinkedList *llist, Literator *p) {
    Ldata *ldata = llist->head;
    for(int i = 0; i < llist->size; i++) {
        if (ldata->data == p->data) {
            ldata->prev->next = ldata->next;
            ldata->next->prev = ldata->prev;
            break;
        }
    }

    free(ldata->data);
    free(ldata);
    llist->size--;

    return LLIST_OK;
}

LLIST_CODE LList_remove_pos(LinkedList *llist, u32 pos) {
    Ldata *ldata = llist->head;

    for(int i = 0; i < pos; i++) {
        ldata = ldata->next;
        if (ldata == NULL) {
            return LLIST_ERROR;
        }
    } 
    
    ldata->prev->next = ldata->next;
    ldata->next->prev = ldata->prev;

    free(ldata->data);
    free(ldata);
    llist->size--;

    return LLIST_OK;
}

Literator *LList_get_iterator(LinkedList *llist) {
    Literator *it = (Literator *) malloc(sizeof(Literator));

    it->data = llist->head->data;
    it->llist_data = llist->head;
    it->llist = llist;

    return it;
}

void LList_iterator_next(Literator *p) {
    if (p->llist_data->next != NULL) {
        p->llist_data = p->llist_data->next;
        p->data = p->llist_data->data;
    } else {
        p->llist_data = NULL;
        p->data = NULL;
    }
}

void Llist_iterator_prev(Literator *p) {
    if (p->llist_data->prev != NULL) {
        p->llist_data = p->llist_data->prev;
        p->data = p->llist_data->data;
    }
}

LLIST_CODE LList_iterator_free(Literator *p) {
    free(p);
    p = NULL;
    return LLIST_OK;
}

LLIST_CODE LList_destroy_list(LinkedList *llist, void (*struct_free)(pointer)) {
    Ldata *ldata = llist->head;

    while(ldata != NULL) {
        Ldata *temp = ldata;
        ldata = ldata->next;

        if (llist->type == L_STRUCT) {
            struct_free(temp->data);
        } else {
            free(temp->data);
        }

        temp->next = NULL;
        temp->prev = NULL;
        free(temp);
        temp = NULL;
    }

    free(llist);
    llist->size = 0;
    llist = NULL;

    return LLIST_OK;
}
