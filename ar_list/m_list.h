#ifndef _M_LIST_
#define _M_LIST_


typedef char boolean;
#define true 1
#define false 0

struct s_list {
    void **list;
    unsigned int len;
    unsigned int max_len;
    boolean concurrent;
};

typedef s_list List;

List *list_create(unsigned int len, boolean concurrency, char *content);
List *list_set_concurrency();
List *list_add(void *value);


#endif //_M_LIST_
