#include <stdio.h>
#include <string.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main(void)
{
	sem_t *sem;
	int ret;
	
	sem = sem_open("/tmp", O_CREAT|O_EXCL, S_IRUSR, 1);
	if(sem == SEM_FAILED)
	{
		fprintf(stderr, "sem_open error[%s]\n", strerror(errno));
	}

	/* 信号量加1 */
	ret = sem_post(sem);
	if(ret == -1)
	{
		fprintf(stderr, "sem_post error[%s]\n", strerror(errno));
	}

	/* 信号量减1 */
	ret = sem_wait(sem);
	if(ret == -1)
	{
		fprintf(stderr, "sem_wait error[%s]\n", strerror(errno));
	}

	/* 返回信号量当前值 */
	int semval;
	ret = sem_getvalue(sem, &semval);
	if(ret == -1)
	{
		fprintf(stderr, "sem_getvalue error[%s]\n", strerror(errno));
	}
	fprintf(stdout, "semval:[%d]\n", semval);

	ret = sem_close(sem);
	if(ret == -1)
	{
		fprintf(stderr, "sem_close error[%s]\n", strerror(errno));
	}

	/* 有名信号量随内核持续，从系统中删除 */
	ret = sem_unlink("/tmp");
	if(ret == -1)
	{
		fprintf(stderr, "sem_unlink error[%s]\n", strerror(errno));
	}

	return 0;
}
