#include <common.h>

#include "log_ext.h"
#include "utils.h"
#include "threads.h"



int thread_create(thread_id_t *tid, const char *name, void *(*routine)(void *), int flag, void *arg)
{
#ifdef OS_LINUX
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	int res, err;

	if (NULL == name) {
		log_fatal("thread cannot created without a name!");
		return -1;
	}

	switch (flag) {
	case THREAD_DETACHED:
		res = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
		break;
	case THREAD_JOINABLE:
		res = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
		break;
	default:
		log_fatal("thread '%s' unknown flag: %d", name, flag);
		res = -1;
	}

	if (res) {
		err = errno;
		log_fatal("thread '%s' setdetachstate failed: %s", name, strerror(err));
		goto err_exit;
	}

	res = pthread_create(tid, &attr, routine, arg);
	if (res) {
		err = errno;
		log_fatal("thread '%s' create failed: %s", name, strerror(err));
		goto err_exit;
	}

	log_info("thread '%s' created!", name);
	pthread_attr_destroy(&attr); /* Not strictly necessary */
	return 0;

err_exit:
	pthread_attr_destroy(&attr);
	return -1;
#else /* OS_LINUX */
	log_fatal("thread_create not support yet!");
	return -1;
#endif /* OS_LINUX */
}

