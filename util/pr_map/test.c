#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define cvt(a) #a

struct tmp {
    char *symbol;
    char *price;
    char *value;
    char *buf;
    char *symbo1;
    char *pric1;
    char *valu1;
    char *bu1;
};

int main() {

    struct tmp *p = malloc(sizeof(*p));




    free(p);

    return 0;
}
