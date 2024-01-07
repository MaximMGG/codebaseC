#include <stdio.h>
#include "async.h"

void print1(int a) {
    printf("%i\n", a);
}
void print2(int a) {
    printf("%i\n", a);
}
void print3(int a) {
    printf("%i\n", a);
}
void print4(int a) {
    printf("%i\n", a);
}



int main() {
    printf("Start job");

    async(&print1);
    async(&print2);
    async(&print3);
    async(&print4);

    async_join;
    printf("Finish job");


    return 0;
}
