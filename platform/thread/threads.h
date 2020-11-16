#ifndef _THREADS_H
#define _THREADS_H


#ifdef OS_LINUX
#include <pthread.h>

enum {
	THREAD_DETACHED = 0,
	THREAD_JOINABLE,
};

typedef pthread_t thread_id_t;

#else
///TODO
#endif /* OS_LINUX */


int thread_create(thread_id_t *tid, const char *name, void *(*routine)(void *), int flag, void *arg);


#endif /* _THREADS_H */

