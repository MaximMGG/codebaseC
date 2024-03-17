#include <assert.h>
#include "../allocator.h"
#include <string.h>

void Allocator_create_test() {
    Allocator *al = Allocator_create(200);
    assert_true(al->chunk_size == 200, "Cunk size not 200");
    assert_true(al->free_chunk_size == 200, "Free cunk size not 200");
    assert_true(al->data_chunk[0] == (char)0xFD, "Cunk[0] != 0xFD");

    Allocator_destroy(al);
}

void Allocator_get_memory_test() {
    Allocator *al = Allocator_create(200);
    int *a = (int *) Allocator_get_memory(al, 4);
    assert_true(*a == 0, "a != 0");
    *a = 888;
    assert_true(*a == 888, "a != 888");

    Allocator_destroy(al);
}

void Allocator_get_memory_fail_test() {
    Allocator *al = Allocator_create(50);
    int *a = Allocator_get_memory(al, 20);
    assert_true(*a == 0, "a != 0");
    int *b = Allocator_get_memory(al, 20);
    *b = 777;
    assert_true(*b == 777, "b != 777");
    int *c = Allocator_get_memory(al, 20);
    assert_null(c, "c not NULL");

    Allocator_destroy(al);
}

void Allocator_get_memory_struct_test() {

    struct T {
        int b;
        double a;
        char *msg;
    }T;
    Allocator *al = Allocator_create(200);

    struct T *t = Allocator_get_memory(al, sizeof(struct T));

    t->a = 2.1;
    t->b = 2;
    t->msg = "Hello";

    assert_true(t->b == 2, "t->b != 2");
    assert_true(strcmp(t->msg, "Hello") == 0, "msg not Hello");

    Allocator_free_memory(al, t);

    assert_true(t->a == 0, "Memory not free");

    Allocator_destroy(al);
}



int main() {
    assert_begin(ASSERT_DEFAULT);
    assert_coll(Allocator_create_test);
    assert_coll(Allocator_get_memory_test);
    assert_coll(Allocator_get_memory_fail_test);
    assert_coll(Allocator_get_memory_struct_test);

    assert_end();

    return 0;
}
