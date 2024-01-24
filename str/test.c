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
    str_free(&b);

    printf("string is %s, len is %d\n", a.str, a.len);

    str fmt = STR("Name is %s, age is %d, time is %ld", fmt);
    char *name = "Billy";
    int age = 23;
    long time = 123141414141444;

    a = str_format(a, fmt, name, age, time);
    str_free(&a);
    str_free(&fmt);

    printf("%s\n", a.str);

    str fmt2 = STR("%s, %s, %d, %c, %f, %lf, %ld", fmt2);
    char *one = "One";
    char *two = "Two";
    int three = 123123;
    char four = 'f';
    float five = 1.0;
    double six = 123123.123123;
    long seven = 777777777777;
    str temp = str_format(temp, fmt2, one, two, three, four, five, six, seven);

    printf("%s - %d\n", temp.str, temp.len);

    return 0;
}
