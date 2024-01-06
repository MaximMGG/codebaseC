#include "async.h"
#include <threads.h>
#include <util/queue.h>
#include <stdbool.h>
#include <stdio.h>


#define C_THRD(i) th_##i
#define POOL_SIZE 4
static mtx_t mut[POOL_SIZE];
static thrd_t pool[POOL_SIZE];
static Queue *q = NULL;
static bool work = 1;




static int worker_0(void *func) {
    mtx_lock(&mut[0]);
    void *(*job) = func;
    if (job) {}
    return 0;
}
static int worker_1(void *func) {
    mtx_lock(&mut[0]);
    void *(*job) = func;
    if (job) {}
    return 0;
}
static int worker_2(void *func) {
    mtx_lock(&mut[0]);
    void *(*job) = func;
    if (job) {}
    return 0;
}
int worker_3(void *func) {
    mtx_lock(&mut[0]);
    void *(*job) = func;
    if (job) {}
    return 0;
}





int _thread_manage(void *man) {
    
    while(work) {
        int cur_worker = 0;
        if (get_size(q) == 0) {
            thrd_sleep(&(struct timespec){.tv_nsec = 2000}, NULL);
            printf("I am sleep");
        }
        while(get_size(q) != 0) {

        }
    }
    return 0;
}


void _thread_prepare(void *func) {
    if (q == NULL) q = queue_create();
    queue_add(q, func);
    thrd_t man;
    thrd_create(&man, &_thread_manage, &man);


}









