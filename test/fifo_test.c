#include <common.h>
#include "threads.h"
#include "utils.h"
#include "fifo.h"
#include "log_ext.h"

#define FIFO_SIZE    (1024)

static unsigned char g_fifo_buffer[FIFO_SIZE];
static mutex_t g_fifo_lock;
static struct kfifo *g_fifo;


static void *fifo_push_routine(void *arg)
{
	struct kfifo *fifo = (struct kfifo *) arg;
	long count = 0;

	while (1) {
		count ++;
		kfifo_put(fifo, (unsigned char *) &count, sizeof(count));

		sleep_ms(500);
	}
	return NULL;
}

static void *fifo_pop_routine(void *arg)
{
	struct kfifo *fifo = (struct kfifo *) arg;
	unsigned char buff[FIFO_SIZE];
	unsigned int len;

	while (1) {
		if (kfifo_is_empty(fifo)) {
			//log_info("fifo empty");
		} else {
			len = kfifo_len(fifo);
			memset(buff, 0, len);
			kfifo_get(fifo, buff, len);
			log_info("fifo data len: %d", len);
			dump_hex(buff, len);
			printf("\n");
		}
		sleep_ms(1);
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	thread_id_t tid_push, tid_pop;

	mutex_init(&g_fifo_lock, MUTEX_PRIVATE);
	g_fifo = kfifo_init(g_fifo_buffer, sizeof(g_fifo_buffer), &g_fifo_lock);

	thread_create(&tid_push, "tid_push", fifo_push_routine, THREAD_DETACHED, g_fifo);
	thread_create(&tid_pop, "tid_pop", fifo_pop_routine, THREAD_DETACHED, g_fifo);

	while (1) {
		sleep_s(0xffffffff);
	}
	return 0;
}

