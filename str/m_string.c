#include "m_string.h"
#include <string.h>
#include <stdlib.h>

STR_ERR STR_ERROR;

enum errors{
    CONCAT_ERR,
    MEM_ALLOC_ERR
};


str str_concat(str d, str s) {
    int d_len = strlen(d.str);
    int s_len = strlen(s.str);
    
    char *temp = (char *) malloc(d_len + s_len - 1);
    if (temp == NULL) {
        STR_ERROR = MEM_ALLOC_ERR;
    }
    memcpy(temp, d.str, d_len);
    memcpy(temp + d_len, s.str, s_len);

    int total_len = strlen(temp);
    if (total_len != d_len + s_len) {
        STR_ERROR = CONCAT_ERR;
    }
    d.str = temp;
    d.len = s_len;

    return d;
}

str str_err() {
    str err = STR("Def err");
    switch (STR_ERROR) {
        case MEM_ALLOC_ERR: {
            str e = STR("Memory allocation error");
            err = e;
            break;
            }
        case CONCAT_ERR: {
            str e = STR("String concationation error");
            err = e;
            break;
            }
    }
    return err;
}
