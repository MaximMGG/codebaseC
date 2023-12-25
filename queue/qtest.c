#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main() {

    char *one = "one";
    char *two = "two";
    char *three = "three";

    Queue *q = queue_create();

    queue_add(q, one);
    queue_add(q, two);
    queue_add(q, three);

    printf("%s\n", (char *)queue_get(q));
    printf("%s\n", (char *)queue_get(q));
    printf("%s\n", (char *)queue_get(q));
    printf("%s\n", (char *)queue_get(q));

    return 0;
}
