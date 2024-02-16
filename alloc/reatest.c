#include <stdlib.h>
#include <stdio.h>


int main (){ 
    int  *arr = malloc(sizeof(int) * 10);
    for(int i = 0; i < 10; i++) {
        *(arr + i) = i;
    }
    int *p = &arr[4];
    printf("%p\n", arr);
    printf("%p - %d\n", p, *p);

    arr = realloc(arr, sizeof(int) * 20);
    for(int i = 10; i < 20; i++) {
        *(arr + i) = i;
    }
    int *a = &arr[4];

    printf("%p\n", arr);
    printf("%p - %d\n", p, *p);
    printf("%p - %d\n", a, *a);

    return 0;
}
