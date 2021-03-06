#include "include/apue.h"
#include "include/process.h"

char *env_init[] = {"USER=unknown", "PATH=/tmp", NULL };

int
main(int argc, char *argv[])
{
	pid_t pid;

	if((pid = fork()) < 0)
	{
		err_sys("fork error");
	}
	else if(pid == 0)
	{
		if(execle("/home/sar/bin/echoall", "echoall", "myarg1", "MY ARG2", (char *)0, env_init) < 0)
			err_sys("execle error");
	}
	if(waitpid(pid, NULL, 0) < 0)
		err_sys("wait error");

	if((pid = fork()) < 0)
	{
		err_sys("wait error");
	}
	else if(pid == 0)
	{
		if(execlp("echoall", "echoall", "only 1 arg", (char *)0) < 0)
			err_sys("execlp error");
	}

	int i;
	char **ptr;
	extern char **environ;
	for(i = 0; i < argc; i++)
	{
		printf("argv[%d]:%s\n", i, argv[i]);

	}

	for(ptr = environ; *ptr != 0; ptr++)
		printf("%s\n", *ptr);

	exit(0);
}
