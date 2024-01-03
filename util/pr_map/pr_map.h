#ifndef _PR_MAP_H_
#define _PR_MAP_H_


#define STANDARD_PROP_FILE1 "res/property.conf"
#define STANDARD_PROP_FILE2 "../res/property.conf"


struct property {
    char *key;
    char *val;
};

typedef struct property Property;


//take a string and return Property key->value
//string should be like {"key":"value","key2":12345,"a":"b",...}
Property **parse_get_response(char *, int *property_len);
//free all memory in Property
void free_property(Property **y_prop, int property_len);
/*
 * set property in struct, struct should be like in example:
 * struct your_map {
 *      char *key_prop1;
 *      char *key_prop2;
 *      char *key_prop3;
 *      ...
 * }
 * void *y_struct need to set pointer on struct the need to fill
 * struct atributes should put in the same way from first to last like in http response
 * unsigned int size -> here need to set count alements in  "void *y_struct"
 * if struct countein 3 elements, set size = 3;
 * return pointer on y_struct
*/
void *set_property_in_struct_map(unsigned int size, void *y_struct, Property **pr);

//return value of property with key; 
//name=Bob -> return Bob if filename == NULL, check standard repos
//res/property.conf or ../res/property.conf
char *get_property_from_file(char *filename, char *key);

//free all memory in y_struct
void free_struct_map(void *y_struct, unsigned int size);

//parse line in format key=value to struct Property
Property *parse_property(char *line);


#endif // _PR_MAP_H_
