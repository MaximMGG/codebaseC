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
    str *four = str_concat(one, two, 0);

    str *buf = cr_str("Hello World!");
    str *bu = cr_str("HelloWorld!");

    assert(str_cmp(tree, buf));
    assert(str_cmp(four, bu));

    destroyAll(6, one, one, two, tree,four, bu, buf);
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

void testGetStringBetween() {

    str *reference = cr_str("hello from my_string");
    char *target = "<something>hello from my_string</something>";
    char *target2 = "asd&hello from my_string&xbzcxb";
    char *target3 = "nvudka!(#)_hello from my_string/x(&^#())bzcxb";

    str *result = cr_str(get_str_between(target, '>', '<'));
    assert(str_cmp(reference, result));
    result = cr_str(get_str_between(target2, '&', '&'));
    assert(str_cmp(reference, result));
    result = cr_str(get_str_between(target3, '_', '/'));
    assert(str_cmp(reference, result));

    destroyAll(2, reference, result);
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
    puts("Test string get between to symbols");
    testGetStringBetween();
    puts("Test string get between to symbols -> success");
    puts("----------------------------------------------------");

    return 0;
}
