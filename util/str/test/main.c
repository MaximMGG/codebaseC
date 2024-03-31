#include <util/m_string.h>
#include <assert.h>
#include <string.h>

void str_append_test() {

    str *a = newstr("Hello");
    assert_not_null(a, "str is NULL");
    a = str_append(a, " world!");
    assert_true(strcmp("Hello world!", a->str) == 0, "Strings not the same");

    char *name = " Billy\0";

    for(int i = 0; name[i] != '\0'; i++) {
        a = str_append(a, &name[i]);
    }

    assert_true(strcmp("Hello world! Billy", a->str) == 0, "Billy not added");
}



int main() {

    assert_begin(ASSERT_DEFAULT);
    assert_coll(str_append_test);
    assert_end();

    return 0;
}
