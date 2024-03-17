#include "../m_linkedlist.h"
#include <string.h>


typedef struct {
    char *name;
    int *sum;
    double *big_sum;
} app;

void free_app(void *a) {
    app *A = (app *)a;

    if (A->name != NULL) {
        free(A->name);
        A->name = NULL;
    }
    if (A->sum != NULL) {
        free(A->sum);
        A->sum = NULL;
    }
    if (A->big_sum != NULL) {
        free(A->big_sum);
        A->big_sum = NULL;
    }
    free(A);
    a = NULL;
}



int main() {
    LinkedList *list = LList_create(L_INT);
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    for(int i = 0; i < 10; i++) {
        LList_append_next(list, &arr[i], 4);
    }
    Literator *it = LList_get_iterator(list);
    for(int i = 0; i < 10; i++) {
        printf("%d\n", *(int *)it->data);
        LList_iterator_next(it);
    }

    LList_destroy_list(list, NULL);
    LinkedList *slist = LList_create(L_STRUCT);

    for(int i = 0; i < 5; i++) {
        app *a1 = (app *) malloc(sizeof(app));
        a1->name = (char *) malloc(sizeof(char) * 10);
        strcpy(a1->name, "Hylia");
        a1->sum = (int *) malloc(sizeof(int) * 10);
        a1->big_sum = (double *) malloc(sizeof(double) * 10);
        a1->name[0] += i;
        for(int j = 0; j < 10; j++) {
            a1->sum[j] = j + i;
            a1->big_sum[j] = j + i + 0.1;
        }
        LList_append_next(slist, a1, sizeof(app));
    }

    it = LList_get_iterator(slist);

    for(int i = 0; i < 5; i++) {
        app *t = (app *)it->data;
        printf("%s -> ", t->name);
        for(int j = 0; j < 10; j++)  {
            printf("%d ", t->sum[j]);
        }
        printf(" || ");
        for(int j = 0; j < 10; j++) {
            printf("%lf ", t->big_sum[j]);
        }
        printf("\n");
        LList_iterator_next(it);
    }

    LList_destroy_list(slist, free_app);

    return 0;
}
