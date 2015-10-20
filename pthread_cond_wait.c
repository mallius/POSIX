#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int ret;
int count = 0;

pthread_cond_t cv = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mp = PTHREAD_MUTEX_INITIALIZER;

void handler(void)
{
	sleep(5);
	if(count == 0)
	{
		pthread_mutex_lock(&mp);

		count++;
		pthread_cond_signal(&cv);

		pthread_mutex_unlock(&mp);
	}
	fprintf(stdout, "计数器加1.\n");
}

void broadcast(void)
{
	int ret;
	sleep(2);
	ret = pthread_cond_broadcast(&cv);
	if(ret)
	{
		fprintf(stderr, "pthread_cond_broadcast error.\n");
		return ;
	}
	fprintf(stdout, "解除条件等待.\n");
	return ;
}
int main(void)
{
	pthread_t tid1;
	pthread_t tid2;
	count = 0;


	/* 创建线程解除条件等待 */
	ret = pthread_create(&tid2, NULL, broadcast, NULL);
	if(ret)
	{
		fprintf(stderr, "phtread_create tid2 error.\n");
		return ret;
	}

	/* 创建线程为计数器加1 */
	ret = pthread_create(&tid1, NULL, handler, NULL);
	if(ret)
	{
		fprintf(stderr, "pthread_create tid1 error.\n");
		return ret;
	}

	/* 计数器为0则条件等待 */
	pthread_mutex_lock(&mp);
	while(count == 0)
	{
		fprintf(stdout, "等待中...\n");
		pthread_cond_wait(&cv, &mp);
		fprintf(stdout, "等待完毕ok\n");
	}
	count = 0;
	pthread_mutex_unlock(&mp);

	pthread_join(tid1, NULL);
	fprintf(stdout, "ok\n");

	/* 销毁条件变量 */
	if(pthread_cond_destroy(&cv) || 
	   pthread_mutex_destroy(&mp))
	{
		fprintf(stderr, "destroy error.\n");
		return -1;
	}

	return 0;
}
