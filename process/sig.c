#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

static void sig_quit(int);

int 
main(void)
{
	sigset_t newmask, oldmask, pendmask;
	if(signal(SIGQUIT, sig_quit) == SIG_ERR)
	{
		fprintf(stderr, "can't catch SIGQUIT");
	}
	/*
	 * Block SIGQUIT and save current signal mask
	 */
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGQUIT);
	if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
	{
		fprintf(stderr, "SIG_BLOCK error");
	}
	sleep(5);
	if(sigpending(&pendmask) < 0)
	{
		fprintf(stderr, "sigpending error");
	}
	if(sigismember(&pendmask, SIGQUIT))
	{
		fprintf(stdout, "\nSIGQUIT pending\n");
	}
	/*
	 * Reset signal mask which unblocks SIGUIT.
	 */
	if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
	{
		fprintf(stderr, "SIG_SETMASK error");
	}
	fprintf(stdout, "SIGQUIT unblockded\n");

	sleep(5);
	exit(0);
}

static void 
sig_quit(int signo)
{
	fprintf(stdout, "caught SIGQUIT\n");
	if(signal(SIGQUIT,SIG_DFL)==SIG_ERR)
		fprintf(stderr, "can't reset SIGQUIT");
}
