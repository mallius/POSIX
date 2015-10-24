#include <setjmp.h>
#include <time.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

static void sig_usr1(int);
static void sig_alrm(int);
static sigjmp_buf jmpbuf;
static volatile sig_atomic_t canjump;

int main(void)
{
	int ret;

	if(signal(SIGUSR1, sig_usr1) == SIG_ERR)
	{
		printf("signal (SIGUSR1) error");
	}

	if(signal(SIGALRM, sig_alrm) == SIG_ERR)
	{
		printf("signal(SIGALRM) error");
	}

	printf("starting main: ");

	ret = sigsetjmp(jmpbuf, 1);
	if(ret)
	{
		printf("end main: ");
		exit(0);
	}
	canjump = 1;

	for(;;)
		pause();
}

void
pre_mask(const char *str)
{
	sigset_t sigset;
	int errno_save;

	errno_save = errno;
	if(sigprocmask(0, NULL, &sigset) < 0)
	{
		
	}
}
