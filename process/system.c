#include "include/apue.h"
#include "include/process.h"

int
main(int argc, char *argv[])
{
	int status;
	if((status = system("date")) < 0)
		err_sys("ststem() error");
	pr_exit(status);

	if((status = system("nosuchcommand")) < 0)
		err_sys("ststem() error");
	pr_exit(status);

	if((status = system("who; exit 44")) < 0)
		err_sys("system() error");
	pr_exit(status);

	if((status = system("ls -l; ")) < 0)
		err_sys("system ls -l error");
	pr_exit(status);

	if(argc < 2)
		err_quit("command-line argument required");

	printf("real uid = %d, effective uid = %d\n", getuid(), geteuid());

	if((status = system(argv[1])) < 0)
		err_sys("system() error");
	pr_exit(status);

	exit(0);
}
