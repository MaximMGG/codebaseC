#include "m_list.h"
#include <stdio.h>
#include <stdlib.h>



int main() {
    List *list = list_create(0, M_INT);
    int a1 = 1;
    int a2 = 2;
    int a3 = 3;
    int a4 = 4;
    int a5 = 5;
    int a6 = 6;

    list_add(list, &a1);
    list_add(list, &a2);
    list_add(list, &a3);
    list_add(list, &a4);
    list_add(list, &a5);

    list_contein(list, &a3);
    list_contein(list, &a6);

    printf("%d\n", *(int *)list_get(list, 0));
    printf("%d\n", *(int *)list_get(list, 1));
    printf("%d\n", *(int *)list_get(list, 2));
    printf("%d\n", *(int *)list_get(list, 3));
    printf("%d\n", *(int *)list_get(list, 4));
    puts("---");

    list_remove(list, &a3);

    printf("%d\n", *(int *)list_get(list, 0));
    printf("%d\n", *(int *)list_get(list, 1));
    printf("%d\n", *(int *)list_get(list, 2));
    printf("%d\n", *(int *)list_get(list, 3));
    // printf("%d\n", *(int *)list_get(list, 4));
    puts("---");


    list_free_all(list);

    char *string_list = "1, 2, 3, 4, 5";
    list = list_create_from_string(string_list, M_INT);

    printf("%d\n", *(int *)list_get(list, 0));
    printf("%d\n", *(int *)list_get(list, 1));
    printf("%d\n", *(int *)list_get(list, 2));
    printf("%d\n", *(int *)list_get(list, 3));
    printf("%d\n", *(int *)list_get(list, 4));
    puts("---");

    list_free_all(list);

    int **arr_list = (int **) malloc(sizeof(int *) * 5);
    for(int i = 0; i < 5; i++) {
        arr_list[i] = (int *) malloc(sizeof(int));
        *arr_list[i] = i + 1;
    }
    list = list_create_from_array((void **)arr_list, M_INT, 5);

    printf("%d\n", *(int *)list_get(list, 0));
    printf("%d\n", *(int *)list_get(list, 1));
    printf("%d\n", *(int *)list_get(list, 2));
    printf("%d\n", *(int *)list_get(list, 3));
    printf("%d\n", *(int *)list_get(list, 4));
    puts("---");

    list_free_all(list);

    char *s1 = "String1";
    char *s2 = "String2";
    char *s3 = "String3";
    char *s4 = "String4";
    char *s5 = "String5";

    list = list_create(0, M_STRING);

    list_add(list, s1);
    list_add(list, s2);
    list_add(list, s3);
    list_add(list, s4);
    list_add(list, s5);

    printf("%s\n", (char *)list_get(list, 0));
    printf("%s\n", (char *)list_get(list, 1));
    printf("%s\n", (char *)list_get(list, 2));
    printf("%s\n", (char *)list_get(list, 3));
    printf("%s\n", (char *)list_get(list, 4));
    puts("---");


    list_remove(list, "String1");
    printf("%s\n", (char *)list_get(list, 0));
    printf("%s\n", (char *)list_get(list, 1));
    printf("%s\n", (char *)list_get(list, 2));
    printf("%s\n", (char *)list_get(list, 3));
    puts("---");

    list_free_all(list);

    char *str_buf = "abx1, abx2, abx3, abx4, abx5";

    list = list_create_from_string(str_buf, M_STRING);
    printf("%s\n", (char *)list_get(list, 0));
    printf("%s\n", (char *)list_get(list, 1));
    printf("%s\n", (char *)list_get(list, 2));
    printf("%s\n", (char *)list_get(list, 3));
    printf("%s\n", (char *)list_get(list, 4));
    puts("---");

    list_free_all(list);

    return 0;
}
