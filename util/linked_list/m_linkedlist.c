#include "m_linkedlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

LinkedList *LList_create() {
    LinkedList *llist = (LinkedList *) malloc(sizeof(LinkedList));
    llist->size = 0;
    llist->head = NULL;
    llist->tail = NULL;
    return llist;
}

static LLIST_CODE LList_append(LinkedList *llist, void *data, u32 size, u32 pos) {
    Ldata *ldata = (Ldata *) malloc(sizeof(Ldata));
    ldata->data = (pointer) malloc(size);
    memcpy(ldata->data, data, size);
    switch (pos) {
        case 0: {
            ldata->next = llist->head;
            ldata->prev = NULL;
            llist->head = ldata;
        } case -1: {
            ldata->next = NULL;
            ldata->prev = llist->tail;
            llist->tail = ldata;
        } default: {
            Ldata *p = llist->head;
            for(int i = 0; i < pos; i++) {
                p = p->next;
            } 
            ldata->prev = p->prev;
            ldata->next = p;
            p->prev = ldata;
        }
    } 
    return LLIST_OK;
}

static LLIST_CODE LList_append_helper(LinkedList *llist, void *data, u32 size, Type type, u32 pos) {
    switch(type) {
        case L_CHAR:
        case L_SHORT:
        case L_INT:
        case L_LONG: {
            if (LList_append(llist, data, type, pos) == LLIST_OK) {
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

LLIST_CODE LList_append_next(LinkedList *llist, void *data, u32 size, Type type) {
    if (LList_append_helper(llist, data, size, type, -1) == LLIST_OK) {
        return LLIST_OK;
    } else {
        return LLIST_ERROR;
    }
}
LLIST_CODE LLIst_append_prev(LinkedList *llist, void *data, u32 size, Type type) {
    if (LList_append_helper(llist, data, size, type, 0) == LLIST_OK) {
        return LLIST_OK;
    } else {
        return LLIST_ERROR;
    }

    return LLIST_OK;
}
LLIST_CODE LList_append_pos(LinkedList *llist, void *data, u32 size, Type type, u32 pos) {
    if (LList_append_helper(llist, data, size, type, pos) == LLIST_OK) {
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
    }
}

void Llist_iterator_prev(Literator *p) {
    if (p->llist_data->prev != NULL) {
        p->llist_data = p->llist_data->prev;
        p->data = p->llist_data->data;
    }
}

LLIST_CODE LList_destroy_list(LinkedList *llist, Type type, void (*struct_free)(pointer)) {
    Ldata *ldata = llist->head;

    while(ldata != NULL) {
        Ldata *temp = ldata;
        ldata = ldata->next;

        if (type == L_STRUCT) {
            struct_free(temp->data);
        } else {
            free(temp->data);
        }

        temp->next = NULL;
        temp->prev = NULL;
        free(temp);
    }

    return LLIST_OK;
}
