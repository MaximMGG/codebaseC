#include <assert.h>
#include "../allocator.h"

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


int main() {
    assert_begin(ASSERT_DEFAULT);
    assert_coll(Allocator_create_test);
    assert_coll(Allocator_get_memory_test);
    assert_coll(Allocator_get_memory_fail_test);

    assert_end();

    return 0;
}
