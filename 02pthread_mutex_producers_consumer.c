#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "lib/PosixWrapper.h"

#define MAX_ITEMS 100
#define MAX_THREADS 10
typedef struct share {
	pthread_mutex_t mutex;
	int buff[MAX_ITEMS];
	int nput;
	int nval;

} share_t;

share_t share = {
	.mutex = PTHREAD_MUTEX_INITIALIZER};

void * producers(void *arg)
{
	int i = 0;

	fprintf(stdout, "producer.\n");
	for(i = 0; i < 10; i++)
	{
		Pthread_mutex_lock(&share.mutex);
		share.buff[share.nput] = share.nval;
		share.nput++;
		share.nval++;
		Pthread_mutex_unlock(&share.mutex);
		*((int *)arg) += 1;
	}

}

void * consumer(void *arg)
{
	int i;
	fprintf(stdout, "consumer.\n");
	for(i = 0; i < 10; i++)
	{
		if(share.buff[i] != i)
		{
			printf("buff[%d] = %d\n", share.buff[i]);
		}
	}	
	return NULL;
}

int main(void)
{
	int count[MAX_THREADS];
	pthread_t tid_producers[MAX_THREADS];
	pthread_t tid_consumer;
	int i = 0;

	/* 创建生产者线程 */
	for(i = 0; i < MAX_THREADS; i++)
	{

		count[i] = 0;
		Pthread_create(&tid_producers[i], NULL, producers, &count[i]);
	}	

	/* 创建消费者线程 */
	Pthread_create(&tid_consumer, NULL, consumer, NULL);

	for(i = 0; i < MAX_THREADS; i++)
	{
		Pthread_join(tid_producers[i], NULL);
		fprintf(stdout, "coutn[%d] = %d\n", i, count[i]);
	}
	
	Pthread_join(tid_consumer, NULL);

	return 0;
}

/* file end */


