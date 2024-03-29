#include "util.h"



void *q_malloc(unsigned int size, char *msg) {
    void *new = malloc(size);
    if(new == NULL) {
        fprintf(stderr, "%s\n", msg);
        exit(1);
    }
    return new;
}
