#ifndef ALLOCATOR_H_
#define ALLOCATOR_H_
#include <stdlib.h>
#include <threads.h>

#define null NULL

typedef struct {
    void *cur_pointer;
    size_t size;
    size_t mem_left;
} allocator;

typedef enum {
    ALLOCATOR_MALLOC_ERROR = 1, 
    ALLOCATOR_LEFTMEM_ERROR = 2,
    ALLOCATOR_OVERSIZE_ERROR = 3

} ALLOCATOR_ERROR;

allocator *allocator_alloc(size_t size);
void *al_get_mem(allocator *al, size_t size);
void al_free(allocator* al);
char *al_get_error();

#endif 

