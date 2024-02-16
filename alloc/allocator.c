#include "allocator.h"
static int allocator_error = 0;

allocator *allocator_alloc(size_t size) {
    allocator *a = (allocator *) malloc(sizeof(allocator));
    if (a == null) {
        allocator_error = ALLOCATOR_MALLOC_ERROR;
        return null;
    }
    a->cur_pointer = (void *) malloc(size);
    if (a->cur_pointer == null) {
        allocator_error = ALLOCATOR_MALLOC_ERROR;
        return null;
    }
    a->size = size;
    a->mem_left = size;

    return a;
}

void *al_get_mem(allocator *al, size_t size) {
    if (size > al->size) {
        allocator_error = ALLOCATOR_OVERSIZE_ERROR;
        return null;
    }
    if (size > al->mem_left) {
        allocator_error = ALLOCATOR_LEFTMEM_ERROR;
        return null;
    }
    void *p = al->cur_pointer;
    al->cur_pointer += size;
    al->mem_left -= size;

    return p;
}
void al_free(allocator* al) {
    al->cur_pointer = al;
    free(al->cur_pointer);
    free(al);
}

char *al_get_error() {
    switch (allocator_error) {
        case ALLOCATOR_MALLOC_ERROR: {
            allocator_error = 0;
            return "ALLOCATOR: malloc() func error\n";
        }
        case ALLOCATOR_OVERSIZE_ERROR: {
            allocator_error = 0;
            return "ALLOCATOR: size is bigger then allocator->size\n";
        }
        case ALLOCATOR_LEFTMEM_ERROR: {
            allocator_error = 0;
            return "ALLOCATOR: size is bigger then allocator->mem_left\n";
        }
    }
    return "OK";
}
