#include "queue.h"
#include <stdlib.h>
#include <threads.h>
#include <string.h>

static mtx_t mutex;


Queue *queue_create() {
    Queue *q = malloc(sizeof(Queue));
    q->first = NULL;
    q->last = NULL;
    q->size = 0;
    mtx_init(&mutex, mtx_plain | mtx_recursive);
    return q;
}

void queue_add(Queue *q, void *ptr_p) {
    mtx_lock(&mutex);
    struct one_step *tmp = malloc(sizeof(*tmp));
    tmp->ptr = ptr_p;
    if (q->size == 0) {
        tmp->next = NULL;
        tmp->prev = NULL;
        q->first = tmp;
        q->last = tmp;
    } else {
        if (q->first == q->last) {
            q->first = tmp;
            q->first->next = q->last;
            q->last->prev = q->first;
        } else {
            tmp->next = q->first;
            q->first->prev = tmp;
            q->first = tmp;
        }
    }
    q->size++;
    mtx_unlock(&mutex);
}

void *queue_get(Queue *q) {
    mtx_lock(&mutex);
    if (q->size == 0) {
        return (void *) "Queue is apty\0";
    }
    struct one_step *tmp;
    if (q->last == q->first) {
        tmp = q->first;
        q->first = NULL;
        q->last = NULL;
    } else {
        tmp = q->last;
        q->last = q->last->prev;
        q->last->next = NULL;
    }
    void *p = tmp->ptr;
    free(tmp);
    q->size--;
    mtx_unlock(&mutex);
    return p;
}
