#include <util/m_string.h>
#include <assert.h>
#include <string.h>

void str_append_test() {
    str a = newstr_l("Hello");
    assert_not_null(a.str, "String is null");
    assert_true(strcmp(a.str, "Hello") == 0, "Str no Hello");
    assert_true(a.len == 5, "Len not 5");
    str_free_l(&a);
    assert_null(a.str, "After free str not NULL");
    assert_true(a.len == 0, "Len not 0");
}



int main() {

    assert_begin(ASSERT_DEFAULT);
    assert_coll(str_append_test);
    assert_end();

    return 0;
}
