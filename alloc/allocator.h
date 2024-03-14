#ifndef ALLOCATOR_H_
#define ALLOCATOR_H_

typedef char byte;

typedef struct {
    byte *data_chunk;
    unsigned int chunk_size;
    unsigned int free_chunk_size;
}Allocator;
/*
 * create Allocator
 * @return Allocator *
 * @param size (size of memory chunk)
*/
Allocator *Allocator_create(unsigned int chunk_size);
/*
 * return pointer on allocated memory memory
 * @return void *
 * @param size (sizeo of allocated memeory)
 */
void *Allocator_get_memory(Allocator *al, unsigned int size);
/*
 * frees allocated memory in chunk
 */
void Allocator_free_memory(Allocator *al, void *mem);
/*
 * return error message
 * @return const char *
 */
const char *Allocator_get_error();
/*
 * frees all memory in Allocator
 */
void Allocator_destroy(Allocator *al);

#endif 
