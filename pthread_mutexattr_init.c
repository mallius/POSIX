#include <pthread.h>
#include <stdio.h>

int main(void)
{
	pthread_mutexattr_t mattr;
	int ret;

	/* initialize an attribute to default value */
	ret = pthread_mutexattr_init(&mattr);
	if(ret)
	{
		fprintf(stderr, "pthread_mutexattr_init error.\n");
		return -1;
	}

	/* 互斥锁的设置范围 */
	ret = pthread_mutexattr_setpshared(&mattr, PTHREAD_PROCESS_PRIVATE);
	if(ret)
	{
		fprintf(stderr, "pthread_mutexattr_setpshared error.\n");
		return -1;
	}

	/* 设置互斥锁类型的属性 */	
	ret = pthread_mutexattr_settype(&mattr, PTHREAD_MUTEX_DEFAULT);
	if(ret)
	{
		fprintf(stderr, "pthread_mutexattr_settype error.\n");
		return -1;
	}

	/* 获取互斥锁的范围 */
	int pshared;
	ret = pthread_mutexattr_getpshared(&mattr, &pshared);
	if(ret)
	{
		fprintf(stderr, "pthread_mutexattr_destroy error.\n");
		return -1;
	}
	fprintf(stdout, "互斥锁范围:[%d]\n", pshared);

	/* 获取互斥锁类型的属性 */
	int type;
	ret = pthread_mutexattr_gettype(&mattr, &type);
	if(ret)
	{
		fprintf(stderr, "pthread_mutexattr_gettype error.\n");
		return -1;
	}
	fprintf(stdout, "互斥锁类型属性:[%d]\n", type);


	ret = pthread_mutexattr_destroy(&mattr);
	if(ret)
	{
		fprintf(stderr, "pthread_mutexattr_destroy error.\n");
		return -1;
	}
	return 0;
}

