#include "include/apue.h"
#include "include/process.h"

int 
main(void)
{

	pid_t pid;
	if((pid = fork()) < 0)
	{
		err_sys("fork error");
	}
	else if(pid == 0)   			/* 第一个子进程 */
	{
		if((pid = fork()) < 0)
			err_sys("fork error");
		else if(pid > 0)
			exit(0);

		/* 第二个子进程 */
		sleep(2);
		printf("second child, parent pid = %d\n", getppid());
		exit(0);
	}
	if(waitpid(pid, NULL, 0) != pid)
		err_sys("waitpid error");

	exit(0);
}
