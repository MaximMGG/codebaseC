#include "allocator.h"
#include <stdio.h>

struct app {
    void *a;
    int b;
    long c;
    char *name;
};

int main() {
    allocator *a = allocator_alloc(200);
    int *arr = al_get_mem(a, 40);
    if (arr == null) printf("%s\n", al_get_error());
    for(int i = 0; i < 10; i++) {
        arr[i] = i;
    }
    char *name = al_get_strmem(a, "Hello, world!");
    if (name == null) {
        printf("%s\n", al_get_error());
    }

    double *darr = al_get_mem(a, sizeof(double) * 16);
    if (darr == null) {
        printf("%s\n", al_get_error());
    }

    for (int i = 0; i < 20; i++) {
        darr[i] = (double) i;
    }
    struct app *aap = al_get_mem(a, sizeof(struct app));
    if (aap == null) printf("%s\n", al_get_error());
    aap->a = name;
    aap->b = 123;
    aap->c = 123123123123;
    aap->name = al_get_strmem(a, "Paul");
    al_free(a);

    return 0;
}
