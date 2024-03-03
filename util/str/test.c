#include <util/m_string.h>
#include <stdio.h>

extern str *str_concat_a(str *a, str *b);
extern str *test_str(str *a);

int main() {

    str *a = newstr("hello");

    str *b = test_str(a);
    printf("%s\n %d\n", b->str, b->len);


    return 0;
}
