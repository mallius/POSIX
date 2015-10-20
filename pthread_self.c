#include <pthread.h>
#include <stdio.h>

int main(void)
{
	int ret;
	pthread_t tid;
	pthread_t tid1, tid2;

	tid = pthread_self();
	ret = pthread_equal(tid1, tid2);
	if(ret)
	{
		fprintf(stderr, "pthread_equal error.\n");
		return -1;
	}	
}
