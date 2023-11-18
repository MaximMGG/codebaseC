#include "linked_list.h"


linked_list * create_linked_list() {
    linked_list *main = malloc(sizeof(*main));
    return main;
}

void add(linked_list *main, void *value) {
    if (main->value == NULL) {
        main->value = value;
    }
    if (main->next == NULL) {
        main->next = create_linked_list();
    }
    linked_list *tmp = 
}
void add_pos(linked_list *main, void *value, int pos);
boolean contains(linked_list *main, void *value);
void delete_value(linked_list *main, int pos);
void destroy_linked_list(linked_list *main);

