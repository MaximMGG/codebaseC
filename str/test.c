#include "m_string.h"
#include <stdio.h>


int main() {

    str *resp_fmt = STR("insert into ticker_%d values('%s', %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %ld, %ld, %ld, %ld, %ld);", resp_fmt);  

    str *f = str_format(NULL, resp_fmt, 1, "BTCUSDT", 12341234.24324, 124123.123414, 12341234.12341234, 0.1234, 1313.1324, 141414.343434, 145656.436456, 34563456.34563456, 0.123123123123, 
            112435345345, 345345345345, 3151515151, 656565656, 777777777);

    printf("%s\n", f->str);

    return 0;
}
