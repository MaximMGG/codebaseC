#include "ar_list.h"
#include <stdio.h>
#include <assert.h>


void test_al_create() {
    a_list *list = al_create(INT, false, 0);
    assert(list->distinct == 0);
    assert(list->len == 0);
    assert(list->max_size == 20);
    assert(list->data_type == INT);

    struct s_test {
        int one;   
        char *two;
        double three;
    };
    al_destroy(list);

    unsigned int size = sizeof(struct s_test *);

    list = al_create(STRUCT, false, sizeof(struct s_test *));
    assert(list->distinct == 0);
    assert(list->len == 0);
    assert(list->max_size == 20);
    assert(list->data_type == STRUCT);
    assert(size == list->struct_size);
}


void test_al_add() {
    a_list *list = al_create(INT, false, 0);
    int a = 123;
    int b = 1234;
    int c = 12345;
    al_add(list, &a, INT);
    al_add(list, &b, INT);
    al_add(list, &c, INT);

    assert(*((int *)list->value[0]) == a);
    assert(*((int *)list->value[1]) == b);
    assert(*((int *)list->value[2]) == c);

    a = 0;
    assert(*((int *)list->value[0]) == 123);
    al_destroy(list);



    list = al_create(STRING, false, 0);
    char *one = "Hello";
    char *two = "Bye";
    char *three = "Baba";

    al_add(list, one, STRING);
    al_add(list, two, STRING);
    al_add(list, three, STRING);

    assert(!strcmp(list->value[0], one));
    assert(!strcmp(list->value[1], two));
    assert(!strcmp(list->value[2], three));
    al_destroy(list);
   
    //test al_add with structs 

    struct s_test {
        int one;
        char *two;
        double three;
    };

    int size = sizeof(struct s_test);

    struct s_test test_st = {12, "Hello", 3.5};
    struct s_test test_st2 = {2, "Bye", 123.999123};
    struct s_test test_st3 = {1299999, "Exterminatus", 312341234.52342};

    list = al_create(STRUCT, false, sizeof(struct s_test));

    al_add(list, &test_st, STRUCT);
    al_add(list, &test_st2, STRUCT);
    al_add(list, &test_st3, STRUCT);


    assert(test_st.one == ((struct s_test *)list->value[0])->one);
    assert(!strcmp(test_st.two, ((struct s_test *)list->value[0])->two));
    assert(test_st.three == ((struct s_test *)list->value[0])->three);

    assert(test_st2.one == ((struct s_test *)list->value[1])->one);
    assert(!strcmp(test_st2.two, ((struct s_test *)list->value[1])->two));
    assert(test_st2.three == ((struct s_test *)list->value[1])->three);

    assert(test_st3.one == ((struct s_test *)list->value[2])->one);
    assert(!strcmp(test_st3.two, ((struct s_test *)list->value[2])->two));
    assert(test_st3.three == ((struct s_test *)list->value[2])->three);
}

//TODO(write functionall to free all lists)
int main() {
    a_list *list;

    puts("BEGIN TESTS");
    puts("Test create ar_list");
    test_al_create();
    puts("Test create ar_list: successs");
    puts("Test al_add");
    test_al_add();
    puts("Test al_add: success");

    return 0;
}
