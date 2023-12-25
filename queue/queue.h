#ifndef _QUEUE_H_
#define _QUEUE_H_

struct one_step {
    void *ptr;     
    struct one_step *prev;
    struct one_step *next;
};

typedef struct queue_s {
    struct one_step *first;
    struct one_step *last;
    int size;
} Queue;

Queue *queue_create();
void queue_add(Queue *q, void *ptr_p);
void *queue_get(Queue *q);

#endif //_QUEUE_H_
