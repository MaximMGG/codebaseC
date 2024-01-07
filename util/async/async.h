#ifndef _ASYNC_H
#define _ASYNC_H
#include <threads.h>


#define async(func) _thread_prepare(func)
#define async_join  _finish_work()

extern void _thread_prepare(void *func);
extern void _finish_work();

#endif //_ASYNC_H
