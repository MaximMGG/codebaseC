#ifndef _ARRAY_H_
#define _ARRAY_H_

//arrays with fix size

typedef struct {
    char *data;
    unsigned int size;
}char_arr;

typedef struct {
    short *data;
    unsigned int size;
}short_arr;

typedef struct {
    int *data;
    unsigned int size;
}int_arr;

typedef struct {
    long *data;
    unsigned int size;
}long_arr;

typedef struct {
    float *data;
    unsigned int size;
}float_arr;

typedef struct {
    double *data;
    unsigned int size;
}double_arr;

typedef struct {
    void *data;
    unsigned int size;
}void_arr;
//------------------
//
// arrays with dynamic size

typedef struct {
    char *data;
    unsigned int size;
    unsigned int max_size;
} dchar_arr;

typedef struct {
    short *data;
    unsigned int size;
    unsigned int max_size;
} dshort_arr;

typedef struct {
    int *data;
    unsigned int size;
    unsigned int max_size;
} dint_arr;

typedef struct {
    long *data;
    unsigned int size;
    unsigned int max_size;
} dlong_arr;

typedef struct {
    float *data;
    unsigned int size;
    unsigned int max_size;
} dfloat_arr;

typedef struct {
    double *data;
    unsigned int size;
    unsigned int max_size;
} ddouble_arr;

typedef struct {
    void *data;
    unsigned int size;
    unsigned int max_size;
} dvoid_arr;

void _free_arr(void_arr *arr);
void *arr_append(void_arr *arr, void *val);

#define CREATE_ARR(type, a_size) type ## _arr *arr = (type ## _arr *) malloc(sizeof(type **_arr));  \
                                            arr->data = (type *) malloc(sizeof(type) * a_size); \
                                            arr->size = a_size;

#define FREE_ARR(arr) _free_arr((void_arr *)arr)

#endif //_ARRAY_H_
