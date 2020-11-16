#include "common.h"

#include <time.h>

void *xmalloc(size_t size)
{
	if (!size)
		size ++;
	return malloc(size);
}

void *zmalloc(size_t size)
{
	if (!size)
		size ++;
	return calloc(1, size);
}

int is_big_endian(void)
{
	union {
		long l;
		char c[sizeof(long)];
	} u;

	u.l = 1;
	return (u.c[sizeof(long) - 1] == 1);
}

time_t get_time(void)
{
    return time(NULL);
}

char *get_ctime(const time_t *t)
{
    char *str_time = ctime(t);
    return str_time ? str_time : "(null)";
}

/**
 * sleep(3) may be implemented using SIGALRM; mixing calls to alarm() and sleep(3) is a bad idea.
 */
void sleep_us(uint32_t us)
{
	usleep(us);
}

void sleep_ms(uint32_t ms)
{
	struct timeval tv;
	tv.tv_sec = 0;
    tv.tv_usec = ms * 1000;
	int err;
    do {
       err = select(0, NULL, NULL, NULL, &tv);
    } while (err < 0 && errno == EINTR);
}

void sleep_s(uint32_t s)
{
	struct timeval tv;
	tv.tv_sec = s;
    tv.tv_usec = 0;
	int err;
    do {
       err = select(0, NULL, NULL, NULL, &tv);
    } while (err < 0 && errno == EINTR);
}

int set_block(int fd)
{
	int flags = fcntl(fd, F_GETFL);
	flags &= ~O_NONBLOCK;
	return fcntl(fd, F_SETFL, flags);
}

int set_nonblock(int fd)
{
	int flags = fcntl(fd, F_GETFL);
	flags |= O_NONBLOCK;
	return fcntl(fd, F_SETFL, flags);
}

int set_cloexec(int fd)
{
	int res;
	int val;

	val = fcntl(fd, F_GETFD, 0);
	if (val < 0) {
		fprintf(stderr, "set_cloexec getfd\n");
		return -1;
	}

	val |= FD_CLOEXEC;
	res = fcntl(fd, F_SETFD, val);
	if (res < 0) {
		fprintf(stderr, "set_cloexec setfd\n");
		return -1;
	}

	return res;
}

