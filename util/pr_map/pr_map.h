#ifndef _PR_MAP_H_
#define _PR_MAP_H_

struct property {
    char *key;
    char *val;
};

typedef struct property Property;


Property **parse_get_response(char *, int *property_len);
/*
 * set property in struct, struct should be like in example:
 * struct your_map {
 *      char *key_prop1;
 *      char *key_prop2;
 *      char *key_prop3;
 *      ...
 * }
 * should put in the same way from first to last like in http response
 * unsigned int size -> here need to set count alements in your_map struct
 * if struct countein 3 elements, set size = 3;
 * return pointer on y_struct
*/
void *set_property_in_struct_map(unsigned int size, void *y_struct, Property **pr);




#endif // _PR_MAP_H_
