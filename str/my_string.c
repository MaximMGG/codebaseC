#include "my_string.h"

unsigned int str_length(char *buf) {
    unsigned int length = 0;
    for(int i = 0; ; i++) {
        if (buf[i] == '\0') {
            length = i;
            break;
        }
    }
    return length;
}


int ** getPacOfDicimal() {
    int **buf = malloc(sizeof(int *) * 9);
    for(int i = 0; i < 9; i++) {
        buf[i] = malloc(sizeof(int));
    }
    *(buf[0]) = BIL;
    *(buf[1]) = MIL_100;
    *(buf[2]) = MIL_10;
    *(buf[3]) = MIL;
    *(buf[4]) = SOU_100;
    *(buf[5]) = SOU_10;
    *(buf[6]) = SOU;
    *(buf[7]) = HAN_100;
    *(buf[8]) = HAN_10;
    return buf;
}

char * mapDoubleToString(double buf) {


    return NULL;
}

str * str_concat(str *first, str *second, char symbol) {
    char* buf = malloc(sizeof(char) * (first->length + second->length));
    int i = 0;
    int j = 0;
    
    for( ; ;i++) {
        if (first->str[i] == '\0') {
            buf[i] = symbol;
            i++;
            break;
        }
        buf[i] = first->str[i];
    }

    for( ; ;i++, j++) {
        if (second->str[j] == '\0') {
            buf[i] = '\0';
            break;
        }
        buf[i] = second->str[j];
    }

    str *new = cr_str(buf);
    free(buf);

    return new;
}

/*
 * return 0 if one and two strings not the same
 * return 1 if one and two strings are the same
*/
int str_cmp(str *one, str *two) {
    unsigned int one_length = str_length(one->str);
    unsigned int two_length = str_length(two->str);

    if (one_length != two_length) {
        return 0;
    } else {
        for(int i = 0; i < one_length; i++) {
            if (one->str[i] != two->str[i]) {
                return 0;
            }
        }
    }
    return 1;
}

char * mapIntToString(int buf) {

    char *s = malloc(sizeof(char) * 10);
    int s_index = 0;
    int tmp;
    int **nums = getPacOfDicimal();

    for(int i = 0; i < 10;i++) {
        if ((tmp = buf / *(nums[i])) > 0) {
            s[s_index] = tmp + 48;
            s_index++;
            buf = buf % *(nums[i]);
        } else if (tmp == 0) {
            if (s_index != 0) {
                s[s_index] = tmp + 48;
                s_index++;
                buf = buf % *(nums[i]);
            }
        }
        if (buf <= 9) {
            s[s_index] = buf + 48;
            s[s_index + 1] = '\0';
            break;
        }
    }

    free(nums);
    return s;
}

char * str_set(char *s) {
    char *buf = malloc(sizeof(char) * str_length(s));
    for(int i = 0; ; i++) {
        if (s[i] == '\0') {
            buf[i] = '\0';
            break;
        }
        buf[i] = s[i];
    }
    return buf;
}

str *cr_str(char *s) {
    str *p_s = malloc(sizeof(char) * str_length(s));
    p_s->str = str_set(s);
    p_s->length = str_length(s);
    return p_s;
}

void * str_cpy(str *to, str *from) {
    to->str = realloc(to, sizeof(char) * (str_length(from->str)));
    if (to->str == NULL) {
        return NULL;
    }

    int length = 0;

    for(int i = 0; ; i++){
        if ((from->str[i] = '\0')) {
            to->str[i] = '\0';
            to->length = i;
            break;
        }
    }
    to->length = length;
    return to;
}

char * _str_cpy(char *target, char *buf) {
    target = malloc(sizeof(char) * str_length(buf));

    for(int i = 0; ; i++) {
        if (buf[i] == '\0') {
            target[i] = '\0';
            break;
        }
        target[i] = buf[i];
    }
    return target;
}


char * insertString(char *s, char *tmp, int pos){
    long a = sizeof(char) * (str_length(s));
    long b = sizeof(char) * (str_length(tmp));
    char *buf = malloc(a + b);
    int index;

    for(index = 0; index < pos; index++){
        buf[index] = s[index];
    }
    
    for(int i = 0; tmp[i] != '\0'; i++, index++){
        buf[index] = tmp[i];
    }

    for(int i = pos + 2; ; i++, index++){
        if (s[i] == '\0') {
            buf[index] = '\0';
            break;
        }
        buf[index] = s[i];
    }
    char * tt;
    tt = _str_cpy(tt, buf);
    free(buf);
    return tt;
}


char * str_format(char *s,...) {
    va_list li;
    va_start(li, s);
    char *buf_s = malloc(sizeof(char *));
    int buf_i;

    for(int i = 0; s[i] != '\0'; i++){
        if (s[i] == '%') {
            switch(s[i + 1]) {
                case 's': {
                    buf_s = va_arg(li, char *);
                    char *temp_s = insertString(s, buf_s, i);
                    s = _str_cpy(s, temp_s);
                    break;
                    }
                case 'd': {
                    buf_i = va_arg(li, int);
                    char *temp_i = insertString(s, mapIntToString(buf_i), i);
                    s = _str_cpy(s, temp_i);
                    break;
                    }
                case '%': {
                    char *temp_symb = insertString(s, "%", i);
                    s = _str_cpy(s, temp_symb);
                    break;
                    }
            }
        }

    }
    va_end(li);
    return s;
}

void str_distroy(str *s) {
    free(s);
}

