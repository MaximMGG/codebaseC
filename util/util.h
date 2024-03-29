#ifndef _UTIL_H_
#define _UTIL_H_
//
#include <stdio.h>
#include <stdlib.h>
//

//Types
typedef char i8;
typedef unsigned char u8;
typedef short i16;
typedef unsigned short u16;
typedef int i32;
typedef unsigned int u32;
typedef long i64;
typedef unsigned long u64;
typedef void * pointer;
//EndTypes

//try(a) if a < 0 or == NULL print ERROR in stderr
#define tryc(c) if ((c) < 0) fprintf(stderr, "File: %s, Line: %d, %s ERROR\n", __FILE__, __LINE__, # c)
#define trys(s) if ((s) < 0) fprintf(stderr, "File: %s, Line: %d, %s ERROR\n", __FILE__, __LINE__, # s)
#define tryi(i) if ((i) < 0) fprintf(stderr, "File: %s, Line: %d, %s ERROR\n", __FILE__, __LINE__, # i)
#define tryl(l) if ((l) < 0) fprintf(stderr, "File: %s, Line: %d, %s ERROR\n", __FILE__, __LINE__, # l)
#define tryf(f) if ((f) < 0) fprintf(stderr, "File: %s, Line: %d, %s ERROR\n", __FILE__, __LINE__, # f)
#define tryd(d) if ((d) < 0) fprintf(stderr, "File: %s, Line: %d, %s ERROR\n", __FILE__, __LINE__, # d)
#define tryp(p) if ((p) == NULL) fprintf(stderr, "File: %s, Line: %d, %s ERROR\n", __FILE__, __LINE__, # p)
//------------------------------------------------

//boolean type
typedef char boolean;
#define true 1
#define false 0

typedef char byte;

void *q_malloc(unsigned int size, char *msg);

#endif //_UTIL_H_
