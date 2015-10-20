#include <pthread.h>
#include <stdio.h>
#include <errno.h>

int main(void)
{
	pthread_t tid;
	int ret;
	struct sched_param param;
	int priority;

	param.sched_priority=priority;
	priority = SCHED_OTHER;
	ret = pthread_setschedparam(tid, priority, &param);
	if(ret == EINVAL || ret==ESRCH)
	{
		fprintf(stderr, "pthread_setschedparam EINVAL or ESRCH error.\n");
		return -1;
	}
	if(ret == ENOTSUP)
	{
		fprintf(stderr, "pthread_setschedparam ENOTSUP error.\n");
		return -1;
	}

	return 0;
}
