#include "m_string.h"

int main() {

    STR a = newstr("Hello");
    STR b = newstr(" World!");

    a = str_concat(a, b);

    printf("%s\n", a);

    free(a - 8);
    free(b - 8);

    return 0;
}
