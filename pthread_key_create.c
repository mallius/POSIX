#include <pthread.h>
#include <stdio.h>

int main(void)
{
	pthread_key_t key;
	int ret;
	void *value;
	int *retVal;
	
	int num = 2;
	value = &num;

	ret = pthread_key_create(&key, NULL);
	if(ret)
	{
		fprintf(stderr, "pthread_key_create error");
		return -1;
	}
	
	ret = pthread_setspecific(key, value);
	if(ret)
	{
		printf("pthread_setspecific error.\n");
		return -1;
	}

	retVal = pthread_getspecific(key);
	if(ret)
	{
		fprintf(stderr, "pthread_getspecific error.\n");
		return -1;
	}
	printf("*retVal[%d]\n", *retVal);

	ret = pthread_key_delete(key);
	if(ret)
	{
		printf("pthread_key_delete error.\n");
		return -1;
	}
}
