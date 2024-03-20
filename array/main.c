#include "array.h"
#include <stdlib.h>
#include <stdio.h>


int main() {
    ARRAY_CREATE(int, 5, arr);

    FOREACH(int, arr) {
        *it = i;
    }

    arr->data[3] = 123;

    FOREACH(int, arr) {
        printf("%d\n", *it);
    }

    ARRAY_CHANGE_SIZE(int, 10, arr);

    FOREACH(int, arr) {
        *it = i + 4;
    }

    FOREACH(int, arr) {
        printf("%d\n", *it);
    }

    ARRAY_FREE(arr);

    return 0;
}
