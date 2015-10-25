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
void pr_mask(const char *);

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

	pr_mask("starting main: ");

	ret = sigsetjmp(jmpbuf, 1);
	if(ret)
	{
		pr_mask("ending main: ");
		exit(0);
	}
	canjump = 1;

	for(;;)
		pause();
}

static void 
sig_usr1(int signo)
{
	time_t startime;

	if(canjump == 0)
		return ;
	pr_mask("starting sig_usr1: ");
	alarm(3);
	startime = time(NULL);
	for(;;)
		if(time(NULL) > startime+5)
			break;
	pr_mask("finishing sig_usr1: ");
	canjump = 0;
	siglongjmp(jmpbuf,1);
}

void
pr_mask(const char *str)
{
	sigset_t sigset;
	int errno_save;

	errno_save = errno;
	if(sigprocmask(0, NULL, &sigset) < 0)
	{
		fprintf(stderr, "sigprocmask error\n");	
	}
	else
	{
		printf("%s", str);
		if(sigismember(&sigset, SIGINT))
			printf(" SIGINT");
		if(sigismember(&sigset, SIGQUIT))
			printf(" SIGQUIT");
		if(sigismember(&sigset, SIGUSR1))
			printf(" SIGUSR1");
		if(sigismember(&sigset, SIGALRM))
			printf(" SIGALRM");
	}
	printf("\n");
	errno = errno_save;
}
