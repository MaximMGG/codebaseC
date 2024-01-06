#ifndef _ASYNC_H
#define _ASYNC_H
#include <threads.h>


#define async(func) _thread_prepare(func)
#define async_join thrd_join(C_THRD(i), 0)

#endif //_ASYNC_H
