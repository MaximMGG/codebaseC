#include "async.h"
#include <threads.h>
#include <util/queue.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


#define POOL_SIZE 4
static mtx_t mut[POOL_SIZE];
static mtx_t man_m;
static thrd_t thrd_pool[POOL_SIZE];
static thrd_t man;
static Queue *q = NULL;
static bool work = false;
static struct func_poll {
    int (*pool[POOL_SIZE])(void *);
} POOL;



static int worker_0(void *func) {
    puts("worker 0 start");
    void *(*job)(void *) = func;
    int b = 1;
    if (job(&b)) {}
    puts("Worker 0 done");
    mtx_unlock(&mut[0]);
    return 0;
}
static int worker_1(void *func) {
    puts("worker 1 start");
    void *(*job)(void *) = func;
    int b = 2;
    if (job(&b)) {}
    puts("Worker 1 done");
    mtx_unlock(&mut[1]);
    return 0;
}
static int worker_2(void *func) {
    puts("worker 2 start");
    void *(*job)(void *) = func;
    int b = 3;
    if (job(&b)) {}
    puts("Worker 2 done");
    mtx_unlock(&mut[2]);
    return 0;
}
static int worker_3(void *func) {
    puts("worker 3 start");
    void *(*job)(void *) = func;
    int b = 3;
    if (job(&b)) {}
    puts("Worker 3 done");
    mtx_unlock(&mut[3]);
    return 0;
}

static void init_pool() {
    POOL.pool[0] = worker_0;
    POOL.pool[1] = worker_1;
    POOL.pool[2] = worker_2;
    POOL.pool[3] = worker_3;
}



static int _thread_manage(void *man) {
    puts("Thred manager init");
    int cur_worker = 0;
    int check = 0;
    while(work) {
        if (get_size(q) == 0) {
            thrd_sleep(&(struct timespec){.tv_nsec = 2000000}, NULL);
            printf("I am sleep");
        }
        while(get_size(q) != 0) {
            if ((check = mtx_trylock(&mut[cur_worker])) == thrd_busy) {
                if (cur_worker >= 4) cur_worker = 0;
                else cur_worker++; 
                continue;
            }
            thrd_create(&thrd_pool[cur_worker], POOL.pool[cur_worker], queue_get(q));
            cur_worker ++;
            if (cur_worker >= 4) {
                cur_worker = 0;
            }
        }
    }
    puts("Thred manager done");
    return 0;
}


void _thread_prepare(void *func) {
    if (q == NULL) q = queue_create();
    queue_add(q, func);
    if (work == false) {
        work = true;
        init_pool();
        thrd_create(&man, _thread_manage, NULL);
    }
}

void _finish_work() {
    work = false;
    thrd_join(man, 0);
    for(int i = 0; i < POOL_SIZE; i++) {
        thrd_join(thrd_pool[i], 0);
        printf("join %i thread\n", i);
    }
    free(q);
    printf("Finish work\n");
}





