#include <pthread.h>
#include <stdio.h>

int cnt = 0;
pthread_mutex_t mp = PTHREAD_MUTEX_INITIALIZER;
pthread_mutexattr_t mattr;
int ret;

int Pthread_mutex_lock(pthread_mutex_t *mutex)
{
	int ret;
	ret = pthread_mutex_lock(mutex);
	if(ret)
	{
		fprintf(stderr, "pthread_mutex_lock erro\n");
		return ret;
	}
	return 0;
}

int Pthread_mutex_trylock(pthread_mutex_t *mutex)
{
	int ret;
	ret = pthread_mutex_trylock(mutex);
	if(ret)
	{
		fprintf(stderr, "pthread_mutex_lock erro\n");
		return ret;
	}
	return 0;
}

int Pthread_mutex_unlock(pthread_mutex_t *mutex)
{
	int ret;
	ret = pthread_mutex_unlock(mutex);
	if(ret)
	{
		fprintf(stderr, "pthread_mutex_unlock erro\n");
		return ret;
	}
	return 0;
}

void handler(void)
{
	Pthread_mutex_lock(&mp);
	cnt++;
	fprintf(stdout, "cnt[%d]\n", cnt);
	Pthread_mutex_unlock(&mp);
}

void handler_try(void)
{
	Pthread_mutex_trylock(&mp);
	cnt++;
	fprintf(stdout, "cnt[%d]\n", cnt);
	Pthread_mutex_unlock(&mp);
}

int main(void)
{

	/* initialize a mutex to its default value */
	ret = pthread_mutex_init(&mp, NULL);
	if(ret)
	{
		fprintf(stderr, "pthread_mutex_init error.\n");
		return -1;
	}
	ret = pthread_mutex_lock(&mp);
	if(ret)
	{
		fprintf(stderr, "pthread_mutex_lock error.\n");
		return -1;
	}
	cnt++;
	ret = pthread_mutex_unlock(&mp);
	if(ret)
	{
		fprintf(stderr, "pthread_mutex_unlock error.\n");
		return -1;
	}
	fprintf(stdout,"cnt:[%d]\n", cnt);

	/* 创建线程20个 */
	int i = 0;
	for(i = 0; i < 10; i++)
	{
		pthread_t tid;
		pthread_t tryTid;
		ret = pthread_create(&tid, NULL, handler, NULL);
		if(ret)
		{
			fprintf(stderr, "pthread_ceate error, i:[%d]", i);
			return ret;
		}
		ret = pthread_create(&tryTid, NULL, handler_try,NULL);
		if(ret)
		{
			fprintf(stderr, "pthread_create(try) error, i:[%d]", i);
			return ret;
		}
	}
	fprintf(stdout,"cnt:[%d]\n", cnt);

	/* 是否需要等待所有进程结束 */

	pthread_mutex_destroy(&mp);
	if(ret)
	{
		fprintf(stderr, "pthread_mutex_destroy error.\n");
		return ret;
	}
	return 0;
}

