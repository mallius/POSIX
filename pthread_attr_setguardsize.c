#include <pthread.h>
#include <stdio.h>


void start_routine(void *arg)
{
	printf("start_routine\n");
}

int main(void)
{
	pthread_attr_t tattr;
	pthread_t tid;
	void *arg;
	int ret;

	/* initialize an attribute to the default value */
	ret = pthread_attr_init(&tattr);
	if(ret)
	{
		fprintf(stderr, "pthread_attr_init error.\n");
		return -1;
	}
	
	size_t guardsize = 10;
	size_t retGuardsize;
	int scope;

	ret = pthread_attr_setguardsize(&tattr, 10);
	if(ret)
	{
		fprintf(stderr, "pthread_attr_setguardsize.\n");
		return -1;
	}

	/* 设置范围 */
	ret = pthread_attr_setscope(&tattr, PTHREAD_SCOPE_SYSTEM);
	if(ret)
	{
		fprintf(stderr, "pthread_attr_setscope erro.\n");
		return -1;
	}

	/* 设置线程并行级别 */
	ret = pthread_setconcurrency(1);
	if(ret)
	{
		fprintf(stderr, "pthread_setconcurrency error.\n");
		return -1;
	}

	ret = pthread_create(&tid, &tattr, start_routine, arg);
	if(ret)
	{
		fprintf(stderr, "pthread_create error.\n");
		return -1;
	}

	ret = pthread_join(tid, NULL);
	if(ret)
	{
		fprintf(stderr, "pthread_join error.\n");
		return -1;
	}

	ret = pthread_attr_getguardsize(&tattr, &retGuardsize);
	if(ret)
	{
		fprintf(stderr, "pthread_attr_getguardsize error.\n");
		return -1;
	}
	fprintf(stdout, "retGuardsize:[%d]\n", retGuardsize);

	/* 获取范围 */
	ret = pthread_attr_getscope(&tattr, &scope);
	if(ret)
	{
		fprintf(stderr, "pthread_attr_getscope error.\n");
		return -1;
	}
	fprintf(stdout, "scope:[%d]\n", scope);

	/* 获取线程并行级别 */
	ret = pthread_getconcurrency();
	fprintf(stdout, "线程并行级别:%d\n", ret);	

	ret = pthread_attr_destroy(&tattr);
	if(ret)
	{
		fprintf(stderr, "pthread_attr_destroy error.\n");
		return -1;
	}
}

