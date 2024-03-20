#include "array.h"
#include <stdlib.h>


void array_free(arr_t *arr) {
    if (arr != NULL) {
        if (arr->data != NULL) {
            free(arr->data);
            arr->data = NULL;
        }
        arr->size = 0;
        free(arr);
        arr = NULL;
    }
}
