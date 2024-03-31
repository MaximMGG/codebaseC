#include "m_string.h"

int main() {

    STR a = newstr("Hello");
    STR b = newstr(" World!");

    a = str_concat(a, b);

    printf("%s\n", a);

    free(a - 8);
    free(b - 8);

    a = newstr("My name is %s and i am a human");

    int i = str_find_first(a, "is");

    printf("%d\n", i);

    i = str_replace_first(a, "%s");

    printf("%s\n", a);

    free(a - 8);

    return 0;
}
