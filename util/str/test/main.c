#include "../m_string.h"
#include <assert.h>
#include <string.h>

void new_str_test() {
    STR a = newstr("Hello");
    STR b = newstr(" World!");

    assert_not_null(a, "a is NULL");
    assert_not_null(b, "a is NULL");

    a = str_concat(a, b);

    assert_true(strcmp(a, "Hello World!") == 0, "a is not Hello World!");

    free(a - 8);
    free(b - 8);
}


int main() {

    assert_begin(ASSERT_DEFAULT);
    assert_coll(new_str_test);
    assert_end();

    return 0;
}
