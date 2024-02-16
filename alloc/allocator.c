#include "allocator.h"
#include <stdio.h>
static int allocator_error = 0;

#define byte char

static void allocator_mem_set(void *dest, byte mem, unsigned int size) {
    byte *dp = (byte *) dest;

    for(int i = 0; i < size; i++) {
        *(dp++) = mem;
    }
}
static void allocator_mem_cpy(void *dest, void *source, unsigned int size) {
    byte *dp = (byte *) dest;
    byte *sp = (byte *) source;

    for(int i = 0; i < size; i++) {
        *(dp++) = *(sp++);
    }
}

static unsigned int allocator_strlen(char *str) {
    unsigned int i = 0;
    for( ; str[i] != '\0'; i++);
    return i;    
}

_Noreturn void allocator_error_print() {
    switch (allocator_error) {
        case ALLOCATOR_MALLOC_ERROR: {
            allocator_error = 0;
            fprintf(stderr, "ALLOCATOR: malloc() func error\n");
        }
        case ALLOCATOR_OVERSIZE_ERROR: {
            allocator_error = 0;
            fprintf(stderr, "ALLOCATOR: size is bigger then allocator->size\n");
        }
        case ALLOCATOR_LEFTMEM_ERROR: {
            allocator_error = 0;
            fprintf(stderr, "ALLOCATOR: size is bigger then allocator->mem_left\n");
        }
    }

    exit(1);
}

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
        allocator_error_print();
        return null;
    }
    if (size > al->mem_left) {
        allocator_error = ALLOCATOR_LEFTMEM_ERROR;
        allocator_error_print();
        return null;
    }
    void *p = al->cur_pointer + (al->size - al->mem_left);
    al->mem_left -= size;
    allocator_mem_set(p, 0, size);

    return p;
}

void *al_get_strmem(allocator *al, char *str) {
    if (str == null) {
        return null;
    }
    unsigned int size = allocator_strlen(str);
    if (size > al->size) {
        allocator_error = ALLOCATOR_OVERSIZE_ERROR;
        allocator_error_print();
        return null;
    }
    if (size > al->mem_left) {
        allocator_error = ALLOCATOR_LEFTMEM_ERROR;
        allocator_error_print();
        return null;
    }
    void *p = al->cur_pointer + (al->size - al->mem_left);
    al->mem_left -= size + 1;
    allocator_mem_cpy(p, str, size);
    char *sp = p;
    sp[size] = '\0';

    return p;
}


void al_free(allocator* al) {
    free(al->cur_pointer);
    al->cur_pointer = null;
    al->size = 0;
    al->mem_left = 0;
    free(al);
    al = null;
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
