#include "PosixWrapper.h"

int Pthread_create(pthread_t *tid, const pthread_attr_t *attr, void * (*func)(void *), void *arg)
{
	int ret;
	if(ret = pthread_create(tid, attr, func, arg))
	{
		fprintf(stderr, "Pthread_create error[%s]\n", strerror(errno));
		return ret;
	}
	return 0;
}

int Pthread_join(pthread_t tid, void **status)
{
	int ret;
	if(ret = pthread_join(tid, status))
	{
		fprintf(stderr, "Pthread_join error[%s]\n", strerror(errno));
		return ret;
	}
	return 0;
}

int Pthread_mutex_lock(pthread_mutex_t * mptr)
{
	int ret;
	if(ret = pthread_mutex_lock(mptr))
	{
		fprintf(stderr, "Pthread_mutex_lock error[%s]\n", strerror(errno));
		return ret;
	}
	return 0;
}

int Pthread_mutex_unlock(pthread_mutex_t * mptr)
{
	int ret;
	if(ret = pthread_mutex_unlock(mptr))
	{
		fprintf(stderr, "Pthread_mutex_unlock error[%s]\n", strerror(errno));
		return ret;
	}
	return 0;
}

