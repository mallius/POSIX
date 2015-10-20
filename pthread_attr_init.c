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

	ret = pthread_create(&tid, &tattr, start_routine, arg);
	if(ret)
	{
		fprintf(stderr, "pthread_create error.\n");
		return -1;
	}

	ret = pthread_join(tid, NULL);

	ret = pthread_attr_destroy(&tattr);
	if(ret)
	{
		fprintf(stderr, "pthread_attr_destroy error.\n");
		return -1;
	}
}

