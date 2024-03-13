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
    allocator->data_chunk = (byte *) malloc(chunk_size + (chunk_size / 4));
    if (allocator->data_chunk == NULL) {
        snprintf(error_message, 256, "Can't allocate %d bytes memory", chunk_size);
        return NULL;
    }
    allocator->chunk_size = chunk_size;
    allocator->free_chunk_size = chunk_size;
    return allocator;
}


