#include "m_string.h"
#include <stdio.h>


int main() {

    str a = STR("Hello", a);
    str b = STR(" Bill", b);

    printf("sting is %s, len is %d\n", a.str, a.len);
    printf("sting is %s, len is %d\n", b.str, b.len);

    a = str_concat(a, b);
    if (STR_ERROR < 0) {
        printf("%s\n", str_err().str);
   }

    printf("string is %s, len is %d\n", a.str, a.len);

    str fmt = STR("Name is %s, age is %d, time is %ld", fmt);
    char *name = "Billy";
    int age = 23;
    long time = 123141414141444;

    a = str_format(a, fmt, name, age, time);

    printf("%s\n", a.str);

    return 0;
}
