#ifndef _UTILITY_H
#define _UTILITY_H


#define NUM_ELEMENTS(arr) (sizeof(arr) / sizeof(arr[0]))
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

void *xmalloc(size_t size);

/**
 * zmalloc - malloc and zero memory
 */
void *zmalloc(size_t size);

/**
 * If @ptr is NULL, no operation is performed.
 */
#define xfree(ptr) do { free((ptr)); \
		(ptr) = NULL; \
	} while (0)

/**
 * is_big_endian - return true if big endian
 */
int is_big_endian(void);

time_t get_time(void);
char *get_ctime(const time_t *t);

void sleep_us(uint32_t us);
void sleep_ms(uint32_t ms);
void sleep_s(uint32_t s);

int set_block(int fd);
int set_nonblock(int fd);

/**
 * set_cloexec - enable close-on-exec
 * close-on-exec flag is important when designing muti-process programs!
 */
int set_cloexec(int fd);

#endif

