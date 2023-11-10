#include <assert.h>
#include "my_string.h"
#include <stdarg.h>

void testStringCreating() {
    str *target = cr_str("Hello world!");
    int ref_len = 13;
    char *ref_string = "Hello world!";

    assert(target->length == ref_len);
    for(int i = 0; i < ref_len; i++) {
        assert(target->str[i] == ref_string[i]);
    }
}



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

//TODO do not compare with symbols ('_', 'Q', ...)
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
    str *tmp = cr_str("I am %s, i am %d years old"); 
    tmp = str_format(tmp, "Bobby", 14);

    assert(str_cmp(reference, tmp));

    destroyAll(2, reference, reference, tmp);
}

void testStringMemCopy() {
    str *from = cr_str("Hello from Penselvania");
    str *to = cr_str("");
    to = str_mem_cpy(to, from, NULL, from->length);

    assert(str_cmp(to, from));

    destroyAll(2, from, to);
}


int main() {
    puts("----------------------------------------------------");
    puts("Test string creationg!");
    testStringCreating();
    puts("Test string creationg! -> success");
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
    puts("Test string mem copy");
    testStringMemCopy();
    puts("Test string mem copy -> success");
    puts("----------------------------------------------------");

    return 0;
}
