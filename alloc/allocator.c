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
    int free_chunk = 0;
    byte *chunk_pointer = al->data_chunk;
    for(int i = 0; i < real_chunk_size; i++) {
        if (*(chunk_pointer) != DEF_BYTE_VAL) {
            free_chunk = 0;
        } else {
            free_chunk++;
        }
        if (free_chunk == size + POINTER_SIZE_INFO) {
            return i;
        }
    }
    return -1;
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

    unsigned int *chunk_size_info = (unsigned int *) (al->data_chunk + chunk_pointer);
    *chunk_size_info = size;
    chunk_pointer += POINTER_SIZE_INFO;

    for(int i = 0; i < size; i++) {
        *(al->data_chunk + chunk_pointer + i) = 0;
    }
    al->free_chunk_size -= size;
    return (void *)(al->data_chunk + chunk_pointer);
}

void Allocator_free_memory(Allocator *al, void *mem) {
    unsigned int *chunk_info = (unsigned int *) (mem - POINTER_SIZE_INFO);
    byte *chunk = (byte *) mem;

    for(int i = 0; i < *chunk_info; i++) {
        *(chunk++) = 0;
    }
    al->free_chunk_size += *chunk_info;
    *chunk_info = 0;
}

void Allocator_destroy(Allocator *al) {
    free(al->data_chunk);
    al->data_chunk = NULL;
    al->chunk_size = 0;
    al->free_chunk_size = 0;
    free(al);
    al = NULL;
}

