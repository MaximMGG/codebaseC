#include <threads.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

#define charp char *


enum Types {
    CHAR, SHORT, INT, LONG, FLOAT, DOUBLE, POINTER
};



struct async_struct {
    void *func;
    int count;
    enum Types t[10];
    void *args[10];
};

struct curc_s {
    int *types;
    void **bufer;
};

int asdf(int a, ...);

void worker_2_args(struct curc_s *job) {
    int c = 0;

    switch(job->types[c]) {
        case CHAR:
            break;
        case SHORT:
            break;
        case INT:
            break;
        case LONG:
            break;
        case FLOAT:
            break;
        case DOUBLE:
            break;
        case POINTER:
            break;
    }
    void *(*aaa)(charp) = job->bufer[0];
}


void async_f_manager(void *function, int count, ...) {

    struct curc_s *job = (struct curc_s *)malloc(sizeof(*job));
    job->bufer = (void **)malloc(sizeof(void *) * count + 1);
    job->types = (int *) malloc(sizeof(int) * count);
    int size = 1;
    int s_count = count;
    job->bufer[0] = function;


    va_list vl;
    va_start(vl, count);
    int type_counter = 0;

    while(s_count--) {
        job->types[type_counter++] = va_arg(vl, int);
    }

    while(count--) {
        job->bufer[size] = (void *)va_arg(vl, void *);
    }

    worker_2_args(job);
}




int thomething(char *one, void *two, int a) {
    return 0;
}


int main() {

    char *b = "Bye";
    char *a = "Hello";
    int n = 123;
    
    async_f_manager(&thomething, 3, POINTER, POINTER, INT, &b, &a, &n);

    return 0;
}
