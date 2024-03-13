#include "allocator.h"
#include <stdlib.h>
#include <stdio.h>

char error_message[256];


Allocator *Allocator_create(unsigned int chunk_size) {
    Allocator *allocator = (Allocator *) malloc(sizeof(Allocator));
    if (allocator == NULL) {
        snprintf(error_message, 256, "Can't allocate %d bytes memory", chunk_size);
        return NULL;
    }
    allocator->data_chunk = (byte *) malloc(chunk_size);
    if (allocator->data_chunk == NULL) {
        snprintf(error_message, 256, "Can't allocate %d bytes memory", chunk_size);
        return NULL;
    }
    allocator->chunk_size = chunk_size;
    allocator->free_chunk_size = chunk_size;
    allocator->_pointers.p_t = (void *) malloc(sizeof(void *) * chunk_size / 8);
    if (allocator->_pointers.p_t == NULL) {
        snprintf(error_message, 256, "Can't allocate %d bytes memory", chunk_size);
        return NULL;
    }
    allocator->_pointers.p_size = (int *) malloc(sizeof(int) * chunk_size / 8);
    if (allocator->_pointers.p_size == NULL) {
        snprintf(error_message, 256, "Can't allocate %d bytes memory", chunk_size);
        return NULL;
    }
}


