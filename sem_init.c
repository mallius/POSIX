#include <semaphore.h>
#include <stdio.h>

int main(void)
{
	sem_t sem;
	int ret;
	int cnt = 4;

	ret = sem_init(&sem, 0, cnt);
	if(ret)
	{
		fprintf(stdout, "sem_init error.\n");
		return ret;
	}

	ret = sem_post(&sem);
	if(ret)
	{
		fprintf(stdout, "sem_post error.\n");
		return ret;
	}

	ret = sem_wait(&sem);
	if(ret)
	{
		fprintf(stderr, "sem_wait error.\n");
		return ret;
	}

	ret = sem_destroy(&sem);
	if(ret)
	{
		fprintf(stdout, "sem_destroy error.\n");
		return ret;
	}
	return 0;
}
