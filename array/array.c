#include "array.h"
#include <stdlib.h>




void _free_arr(void_arr *arr) {
    if (arr != NULL) {
        if (arr->data != NULL) {
            free(arr->data);
            arr->data = NULL;
            arr->size = 0;
        }
        free(arr);
    }
}

void *arr_append(void_arr *arr, void *val) {

}
