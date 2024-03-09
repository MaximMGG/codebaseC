#ifndef ALLOCATOR_H_
#define ALLOCATOR_H_
#include <stdlib.h>
#include <threads.h>

#define null NULL

typedef struct {
    void *pointer;
    unsigned int size;
} _chunk_info;

typedef struct {
    void *cur_pointer;
    size_t size;
    size_t mem_left;
    mtx_t allocator_mutex;

    _chunk_info **chi;
    unsigned int chi_size;
} allocator;

typedef enum {
    ALLOCATOR_OK = 0,
    ALLOCATOR_MALLOC_ERROR = 1, 
    ALLOCATOR_LEFTMEM_ERROR = 2,
    ALLOCATOR_OVERSIZE_ERROR = 3,
    ALLOCATOR_NOT_ALLOC_ERROR = 4,
    ALLOCATOR_NOT_FULLSIZE_CHUNK = 5,
} ALLOCATOR_ERROR;

allocator *allocator_alloc(size_t size);
void *al_get_mem(allocator *al, size_t size);
void *al_get_strmem(allocator *al, char *str);
ALLOCATOR_ERROR al_free(allocator* al, void *pointer);
void al_dealloc(allocator *al);
char *al_get_error();

#endif 

