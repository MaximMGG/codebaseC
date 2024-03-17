#include "../m_list.h"
#include <string.h>
#include <assert.h>

void list_create_test() {
    List *new = list_create(0, l_double);

    assert_not_null(new, "list is null");
    assert_not_null(new->list, "list->list is null");
    assert_true(new->len == 0, "list->len is not 0");
    list_free_all(new);
}

void list_add_test() {
    const char *buf = "hello my name is Bob";
    List *new = list_create_from_string(buf, l_string, " ");
    assert_not_null(new, "list is null");
    assert_true(new->len == 5, "len is not 5");

    char *temp = list_get(new, 0);
    assert_true(strcmp(temp, "hello") == 0, "string do not equalse hello");
    temp = list_get(new, 3);
    assert_true(strcmp(temp, "is") == 0, "string do not equalse is");

    list_free_all(new);
}

void list_add_ingegral_value_test() {
    int a = 12;
    int b = 134;
    int c = 111;
    List *new = list_create(0, l_int);
    list_add(new, &a);
    list_add(new, &b);
    list_add(new, &c);

    assert_true(*(int *)list_get(new, 0) == a, "Not equalse a");
    assert_true(*(int *)list_get(new, 1) == b, "Not equalse b");
    assert_true(*(int *)list_get(new, 2) == c, "Not equalse c");

    list_free_all(new);

    new = list_create(0, l_long);

    long aa = 82783492374;
    long bb = 8111111111;
    long cc = 82783474;
    long dd = 492374;
    list_add(new, &aa);
    list_add(new, &bb);
    list_add(new, &cc);
    list_add(new, &dd);

    assert_true(*(long *)list_get(new, 0) == aa, "Not equalse aa");
    assert_true(*(long *)list_get(new, 1) == bb, "Not equalse bb");
    assert_true(*(long *)list_get(new, 2) == cc, "Not equalse cc");
    assert_true(*(long *)list_get(new, 3) == dd, "Not equalse dd");

    list_free_all(new);

}

void list_add_float_value_test() {
    List *new = list_create(0, l_float);
    float a = 1.2;
    float b = 3.3;
    float c = 12.4;
    list_add(new, &a);
    list_add(new, &b);
    list_add(new, &c);

    assert_true(*(float *) list_get(new, 0) == a, "Not equalse float a");
    assert_true(*(float *) list_get(new, 1) == b, "Not equalse float b");
    assert_true(*(float *) list_get(new, 2) == c, "Not equalse float c");

    list_free_all(new);
    new = list_create(0, l_double);

    double aa = 82783492.374;
    double bb = 8111.111111;
    double cc = 82.783474;
    double dd = 49237.4;

    list_add(new, &aa);
    list_add(new, &bb);
    list_add(new, &cc);
    list_add(new, &dd);

    assert_true(*(double *)list_get(new, 0) == aa, "Not equalse double aa");
    assert_true(*(double *)list_get(new, 1) == bb, "Not equalse double bb");
    assert_true(*(double *)list_get(new, 2) == cc, "Not equalse double cc");
    assert_true(*(double *)list_get(new, 3) == dd, "Not equalse double dd");

    list_free_all(new);
}

void list_free_test() {
    List *new = list_create_from_string("This is a little story", l_string, " ");

    assert_not_null(new, "new is null");
    assert_true(strcmp((char *) list_get(new, 3), "little") == 0, "therd alement not equalse little");

    list_free_all(new);

    assert_null(new->list, "new->list not null");
    assert_null(new, "new not null");


}


int main() {

    assert_begin(ASSERT_SHOW_FUNC | ASSERT_SHOW_FUNC_TIME | ASSERT_SHOW_ASSERT_MSG | ASSERT_SHOW_TOTAL_TIME);
    assert_coll(list_create_test);
    assert_coll(list_add_test);
    assert_coll(list_add_ingegral_value_test);
    assert_coll(list_add_float_value_test);
    assert_coll(list_free_test);


    assert_end();

    return 0;
}
