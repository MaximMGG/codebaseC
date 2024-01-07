#include <stdio.h>
#include "async.h"

void *print1(void *a) {
    for(int i = 0; i < 1000; i++)
        fprintf(stdout, "%i", *(int *) a);
    puts("");
    return NULL;
}
void *print2(void *a) {
    for(int i = 0; i < 1000; i++)
        printf("%i", *(int *) a);
    puts("");
    return NULL;
}
void *print3(void *a) {
    for(int i = 0; i < 1000; i++)
        printf("%i", *(int *) a);
    puts("");
    return NULL;
}
void *print4(void *a) {
    for(int i = 0; i < 1000; i++)
        printf("%i", *(int *) a);
    puts("");
    return NULL;
}



int main() {
    printf("Start job\n");

    async(&print1);
    async(&print2);
    async(&print3);
    async(&print4);
    async(&print1);
    async(&print2);
    async(&print3);
    async(&print4);

    async_join;
    printf("Finish job");


    return 0;
}
