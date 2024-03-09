#include "allocator.h"
#include <stdio.h>

#define DEF_CHUNK_INFO_SIZE 10

static int allocator_error = 0;
#define byte char
typedef byte bool;
#define true 1
#define false 0

static void allocator_mem_set(void *dest, byte mem, unsigned int size) {
    byte _Atomic *dp = (byte _Atomic*) dest;
    for(int i = 0; i < size; i++) {
        *(dp++) = mem;
    }
}

static void allocator_mem_cpy(void *dest, void *source, unsigned int size) {
    byte _Atomic *dp = (byte _Atomic*) dest;
    byte _Atomic *sp = (byte _Atomic*) source;

    for(int i = 0; i < size; i++) {
        *(dp++) = *(sp++);
    }
}

static unsigned int allocator_strlen(char *str) {
    unsigned int i = 0;
    for( ; str[i] != '\0'; i++);
    return i;    
}

static void allocator_add_chunk_info(allocator *aloc, void *point, unsigned int size) {
    byte added = false;
    for(int i = 0; i < aloc->chi_size; i++) {
        if (aloc->chi[i] == NULL) {
            aloc->chi[i] = (_chunk_info *) malloc(sizeof(_chunk_info));
            aloc->chi[i]->pointer = point;
            aloc->chi[i]->size = size;
            added = true;
            return;
        }
    }
    if (added == false) {
        aloc->chi_size <<= 1;
        aloc->chi = (_chunk_info **) realloc(aloc->chi, sizeof(_chunk_info *) * aloc->chi_size);
        aloc->chi[aloc->chi_size / 2] = (_chunk_info *) malloc(sizeof(_chunk_info));
        aloc->chi[aloc->chi_size / 2]->pointer = point;
        aloc->chi[aloc->chi_size / 2]->size = size;
    }
}

static unsigned int allocator_free_chunk_info(allocator *aloc, void *point) {
    unsigned int p_size = {};
    for(int i = 0; i < aloc->chi_size; i++) {
        if (aloc->chi[i] == point) {
            p_size = aloc->chi[i]->size;
            aloc->chi[i]->pointer = NULL;
            aloc->chi[i]->size = 0;
            free(aloc->chi[i]);
            aloc->chi[i] = NULL;
        }
    }
    return p_size;
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
    a->chi_size = DEF_CHUNK_INFO_SIZE;
    a->chi = (_chunk_info **) malloc(sizeof(_chunk_info *) * a->chi_size);

    for(int i = 0; i < a->chi_size; i++) {
        a->chi[i] = NULL;
    }

    allocator_mem_set(a->cur_pointer, 0xdc, size);
    return a;
}

static void *al_get_chunk(allocator *al, size_t size) {
    mtx_lock(&al->allocator_mutex);
    unsigned int count = 0;
    byte ref = 0xdc;
    byte *memp = al->cur_pointer;
    byte *new = null;
    for(int i = 0; i < al->size; i++, memp++) {
        if (*memp == ref) {
            count++;
            if (new == null) {
                new = memp;
            } 
        } else {
            count = 0;
            new = null;
        }
        if (count == size) {
            mtx_unlock(&al->allocator_mutex);
            return new;
        }
    }
    mtx_unlock(&al->allocator_mutex);
    return NULL;
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
    void *p = al_get_chunk(al, size);
    if (p == null) {
        allocator_error = ALLOCATOR_NOT_FULLSIZE_CHUNK;
        return null;
    }
    allocator_add_chunk_info(al, p, size);
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
    void *p = al_get_chunk(al, size + 1);
    if (p == null) {
        allocator_error = ALLOCATOR_NOT_FULLSIZE_CHUNK;
        return null;
    }
    allocator_add_chunk_info(al, p, size);
    al->mem_left -= size + 1;
    allocator_mem_cpy(p, str, size);
    char *sp = p;
    sp[size] = '\0';

    return p;
}


static bool is_memory_in_allocator(allocator *al, void *p){
    return  p >= al->cur_pointer && 
            p <= al->cur_pointer + al->size ? 
            true : false;
}

//0xdc
ALLOCATOR_ERROR al_free(allocator* al, void *p) {
    mtx_lock(&al->allocator_mutex);
    if (is_memory_in_allocator(al, p)) {
        unsigned int size = allocator_free_chunk_info(al, p);
        allocator_mem_set(p, 0xdc, size);
        p = null;
        al->mem_left += size;
        mtx_unlock(&al->allocator_mutex);
        return ALLOCATOR_OK;
    } else {
        mtx_unlock(&al->allocator_mutex);
        return ALLOCATOR_NOT_ALLOC_ERROR;
    }
}

void al_dealloc(allocator *al) {
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

