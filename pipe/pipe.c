#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

#define RD 0
#define WR 1
int main(void)
{
	int fd[2];
	int ret;
	pid_t pid;
	int n1 = 1;
	int n2 = 2;
	int sum1 = 0;
	int sum2 = 0;

	ret = pipe(fd);
	if(ret < 0)
	{
		fprintf(stderr, "pipe error[%s]\n", strerror(errno));
		return ret;
	}
	pid = fork();
	if(pid < 0)
	{
		fprintf(stderr, "fork error[%s]\n", strerror(errno));
		exit(1);
	}
	else if(pid > 0)  //parent
	{
		close(fd[RD]);
		write(fd[WR], &n1, sizeof(int));
		write(fd[WR], &n2, sizeof(int));
		wait(0);
	}
	else
	{
		close(fd[WR]);
		read(fd[RD], &sum1, sizeof(int));
		read(fd[RD], &sum2, sizeof(int));
		printf("sum:[%d]\n", sum1+sum2);
	}

	return 0;
}
