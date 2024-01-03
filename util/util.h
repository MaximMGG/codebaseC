#ifndef _UTIL_H_
#define _UTIL_H_
//
#include <stdio.h>
#include <stdlib.h>
//

#include <util/ar_list.h>
#include <util/queue.h>
#include <util/pr_map.h>

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


#endif //_UTIL_H_
