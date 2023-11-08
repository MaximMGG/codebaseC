#include <assert.h>
#include "my_string.h"
#include <stdarg.h>

void destroyAll(int count, str *tmp, ...) {
    va_list li;
    va_start(li, tmp);

    for (int i = 0; i < count; i++) {
        str *buf = va_arg(li, str *);
        str_distroy(buf);
    }
    va_end(li);
}

void testStringCompare() {
    str* sameOne = cr_str("Bobby");
    str* sameTwo = cr_str("Bobby");

    str* notSame = cr_str("Molly");

    assert(str_cmp(sameOne, sameTwo));
    assert(!str_cmp(sameOne, notSame));

    destroyAll(3, sameOne, sameOne, sameTwo, notSame);

}


void testStringConcat() {
    str *one = cr_str("Hello");
    str *two = cr_str("World!");
    str *tree = str_concat(one, two, ' ');

    str *buf = cr_str("Hello World!");

    assert(str_cmp(tree, buf));

    destroyAll(4, one, one, two, tree, buf);
}

void testStringFormat() {
    str *reference = cr_str("I am Bobby, i am 14 years old");
    str *tmp = cr_str(str_format("I am %s, i am %d years old", "Bobby", 14)); 

    assert(str_cmp(reference, tmp));

    destroyAll(2, reference, reference, tmp);
}



int main() {

    puts("----------------------------------------------------");
    puts("Test comparing string!");
    testStringCompare();
    puts("Test comparing string! -> success");
    puts("----------------------------------------------------");
    puts("Test string concat");
    testStringConcat();
    puts("Test string concat -> success");
    puts("----------------------------------------------------");
    puts("Test string format");
    testStringFormat();
    puts("Test string format -> success");
    puts("----------------------------------------------------");

    return 0;
}
