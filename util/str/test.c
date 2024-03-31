#include "m_string.h"

int main() {

    STR a = newstr("Hello");
    a = newstr_val(a, "Bobby");
    STR b = newstr(" is a human");

    a = str_concat(a, b);

    printf("%s\n", a);

    free(a - 8);
    free(b - 8);

    a = newstr("Hello, my name is %s and i am a Human");

    int i = str_find_first(a, "is");

    a = str_remove_first(a, "%s", &i);
    b = newstr("Bobby");
    a = str_insert(a, b, i);

    printf("%s\n", a);

    free(a - 8);
    free(b - 8);

    a = newstr("Hello, my name is %s, i am %d years old, i am studing in class %c, my average is %f");
    b = str_format(NULL, a, "Bobby", 18, 'A', 2.3);

    printf("%s\n", b);

    str_free(a);
    str_free(b);

    a = newstr("Hello");
    a = str_append(a, " Bobby", 0);

    printf("%s\n", a);

    str_free(a);
    
    a = newstr("Lets count -> ");
    char temp[10] = "abc ";
    for(int i = 0; i < 10; i++) {
        temp[2] += 1;
        a = str_append(a, temp, 0);
        printf("%s\n", a);
    }

    str_free(a);
    return 0;
}
