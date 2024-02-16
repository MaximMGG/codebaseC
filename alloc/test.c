#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main() {
    void *p = sbrk(0);
    int i = 0;
    p = sbrk(1);
    i = brk(p);
    p = sbrk(1);
    i = brk(p);

    p = mmap(p, 10, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
    i = brk(p);
    char *name = p;
    if (p != NULL) {
        strcpy(name, "Paul");
    }
    void *pt = sbrk(0);
    pt = sbrk(10);
    munmap(p, 10);
    void *d = sbrk(40);
    d = mmap(d, 40, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
    int *arr = d;
    for(int i = 0; i < 10; i++) {
        arr[i] = i;
    }
    i = brk(d);

    munmap(arr, 40);

    return 0;
}
