#include "m_string.h"
#include <stdio.h>


int main() {

    str a = STR("Hello");
    str b = STR(" Bill");

    printf("sting is %s, len is %d\n", a.str, a.len);
    printf("sting is %s, len is %d\n", b.str, b.len);

    a = str_concat(a, b);
    if (STR_ERROR < 0) {
        printf("%s\n", str_err().str);
    }

    printf("string is %s, len is %d\n", a.str, a.len);




    return 0;
}
