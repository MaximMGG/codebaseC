#ifndef _ARRAY_H_
#define _ARRAY_H_

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

typedef void_arr arr_t;

#define ARRAY_CREATE(type, arr_size, name) type ## _arr *name = malloc(sizeof(type ## _arr)); \
                                                    name->data = (type *) malloc(sizeof(type) * arr_size);\
                                                    name->size = arr_size

#define ARRAY_CHANGE_SIZE(type, arr_size, name) name->data = (type *) realloc(name->data, sizeof(type) * arr_size); name->size = arr_size
#define ARRAY_FREE(name) if (name != NULL) {if (name->data != NULL) {free(name->data); name->data = NULL; name->size = 0;} free(name); name = NULL;}

// *it is pointer on array->data[0] and it iterated by 1 every sycle, i is
// counter
#define FOREACH(type, array) for(type *it = array->data, i = 0; i < array->size; it++, i++)

#endif //_ARRAY_H_
