#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <threads.h>

static Queue *q;
char doo = 1;


int get_from_queae(void *ptr) {

    int size;
    while (doo) {
        while((size = get_size(q)) > 0) {
            queue_get(q);
            printf("Get value, size is %d\n", size);
        }
    }

    thrd_exit(0);
    return 0;
}


int main() {

    q = queue_create();

    int res = 0;
    thrd_t t;
    thrd_create(&t, &get_from_queae, NULL);

    for(int i = 10; i > 0; i--) {
        queue_add(q, "Hello");
        printf("Add value, size is %d\n", get_size(q));
    }
    doo = 0;

    thrd_join(t, &res);
    return 0;
}
