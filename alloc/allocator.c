#include "allocator.h"
#include <stdlib.h>
#include <stdio.h>

char error_message[256];
#define POINTER_SIZE_INFO 4
#define DEF_BYTE_VAL 0xFD

Allocator *Allocator_create(unsigned int chunk_size) {
    Allocator *allocator = (Allocator *) malloc(sizeof(Allocator));
    unsigned int real_chunk_size = chunk_size + (chunk_size / 4);
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
    byte *iterator = allocator->data_chunk;
    for(int i = 0; i < real_chunk_size; i++) {
        *(iterator++) = DEF_BYTE_VAL;
    }
    return allocator;
}

static int Allocator_check_free_chunk(Allocator *al, unsigned int size) {
    unsigned int real_chunk_size = al->chunk_size + (al->chunk_size / 4);
    for(int i = 0; i < real_chunk_size; i++) {

    }
}

void *Allocator_get_memory(Allocator *al, unsigned int size) {
    if (size > al->chunk_size) {
        snprintf(error_message, 256, "size %u more than current chunk_size %u", size, al->chunk_size);
        return NULL;
    } else if (size > al->free_chunk_size) {
        snprintf(error_message, 256, "size %u more than free chunk_size %u", size, al->free_chunk_size);
        return NULL;
    }
    int chunk_pointer = Allocator_check_free_chunk(al, size);
    if (chunk_pointer == -1) {
        snprintf(error_message, 256, "do not have %u bytes chunk", size);
        return NULL;
    }
    for(int i = 0; i < size; i++) {
        *(al->data_chunk + chunk_pointer + i) = 0;
    }
    return (void *)(al->data_chunk + chunk_pointer);
}

