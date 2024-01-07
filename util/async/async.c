#include "async.h"
#include <threads.h>
#include <util/queue.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


#define POOL_SIZE 4
static mtx_t mut[POOL_SIZE];
static thrd_t pool[POOL_SIZE];
static Queue *q = NULL;
static bool work = false;
static struct func_poll {
    void **pool;
} POOL;



static int worker_0(void *func) {
    mtx_lock(&mut[0]);
    void *(*job) = func;
    if (job) {}
    puts("Worker 0 done");
    mtx_unlock(&mut[0]);
    return 0;
}
static int worker_1(void *func) {
    mtx_lock(&mut[1]);
    void *(*job) = func;
    if (job) {}
    puts("Worker 1 done");
    mtx_unlock(&mut[1]);
    return 0;
}
static int worker_2(void *func) {
    mtx_lock(&mut[2]);
    void *(*job) = func;
    if (job) {}
    puts("Worker 2 done");
    mtx_unlock(&mut[2]);
    return 0;
}
static int worker_3(void *func) {
    mtx_lock(&mut[3]);
    void *(*job) = func;
    if (job) {}
    puts("Worker 3 done");
    mtx_unlock(&mut[3]);
    return 0;
}

static void init_pool() {
    POOL.pool = (void **) malloc(sizeof(void *) * POOL_SIZE);
    POOL.pool[0] = &worker_0;
    POOL.pool[1] = &worker_1;
    POOL.pool[2] = &worker_2;
    POOL.pool[3] = &worker_3;
}



static int _thread_manage(void *man) {
    puts("Thred manager init");
    while(work) {
        int cur_worker = 0;
        if (get_size(q) == 0) {
            thrd_sleep(&(struct timespec){.tv_nsec = 2000}, NULL);
            printf("I am sleep");
        }
        while(get_size(q) != 0) {
            thrd_create(&pool[cur_worker], POOL.pool[cur_worker], queue_get(q));
            cur_worker += cur_worker >= 4 ? -4 : 1;
        }
    }
    puts("Thred manager done");
    return 0;
}


void _thread_prepare(void *func) {
    if (q == NULL) q = queue_create();
    queue_add(q, func);
    if (work == false) {
        thrd_t man;
        work = true;
        thrd_create(&man, &_thread_manage, &man);
    }
}

void _finish_work() {
    work = false;
    for(int i = 0; i < POOL_SIZE; i++) {
        thrd_join(pool[i], 0);
    }
    free(POOL.pool);
    free(q);
    printf("Finish work\n");
}





