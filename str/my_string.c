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
    char* buf = malloc(sizeof(char) * (first->length + second->length) + sizeof(symbol));
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

str *cr_str(char *s) {
    str *p_s = malloc(sizeof(*p_s));
    unsigned int len = str_length(s);
    p_s->str = malloc(sizeof(char) * len);

    for(int i = 0; i < len; i++) {
        p_s->str[i] = s[i];
    }

    p_s->str[len] = '\0';
    p_s->length = len;
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

void * str_mem_cpy(str *to, str *from, unsigned int size) {
    to = realloc(to, sizeof(char) * from->length);
    unsigned int *iTo = (unsigned int *)to->str;
    unsigned int *iFrom = (unsigned int *)from->str;
    
    int val = size / sizeof(int);
    int lastVal = size % sizeof(int);

    for(int i = 0; i < val; i++) {
        *(iTo++) = *(iFrom++);
    }

    unsigned char *cTo = (unsigned char *) iTo;
    unsigned char *cFrom = (unsigned char *) iFrom;

    for(int i = 0; i < lastVal; i++) {
        *(cTo++) = *(cFrom++);
    }

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


void insertString(str *main, char *buf, int pos){
    char *tmp = malloc(sizeof(char) * (main->length * str_length(buf)));
    int i = 0;
    for(; i < pos; i++) {
        tmp[i] = main->str[i];
    }
    for(int j = 0; ; j++, i++) {
        if (buf[j] == '\0') break;
        tmp[i] = buf[j];
    }
    pos += 2;
    if (pos >= main->length) {
        main->str = tmp;
        return;
    }
    for(int j = pos; ; i++, j++) {
        if (main->str[j] == '\0' || main->str[j] == '\n') {
            tmp[j] = '\0';
            break;
        }
        tmp[i] = main->str[j];
    }
    main->str = tmp;
}


str * str_format(str *main,...) {
    va_list li;
    va_start(li, main);

    for(int i = 0; ;i++) {
        if (main->str[i] == '%') {
            switch(main->str[i + 1]) {
                case 's': {
                    char *buf_s = va_arg(li, char *);
                    insertString(main, buf_s, i);
                    break;
                }
                case '%': {
                    insertString(main, "%", i); 
                    break;
                }
                case 'd': {
                    int buf_i = va_arg(li, int);
                    insertString(main, mapIntToString(buf_i), i);
                    break;
                }
            }
        }
        return main;
    }

    va_end(li);
    return s;
}

void str_distroy(str *s) {
    free(s);
}

