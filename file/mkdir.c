#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

int Mkdir(const char *path, mode_t mode)
{
	int ret;
	if((ret = mkdir(path, mode)) < 0)
	{
		fprintf(stderr, "mkdir error[%s]\n", strerror(errno));
		exit(ret);
	}
	return ret;
}
int Rmdir(const char *path)
{
	int ret;
	if((ret = rmdir(path)) < 0)
	{
		fprintf(stderr, "rmdir error[%s]\n", strerror(errno));
		exit(ret);
	}
	return ret;
}
DIR *Opendir(const char *name)
{
	DIR *dir;
	if((dir = opendir(name)) == NULL)
	{
		fprintf(stderr, "opendir error[%s]\n", strerror(errno));
		return NULL;
	}
	return dir;
}
int Closedir(DIR *dir)
{
	int ret;
	if((ret = closedir(dir)) < 0)
	{
		fprintf(stderr, "closedir error[%s]\n", strerror(errno));
		return ret;
	}
	return ret;
}

#define DIRNAME "./testDir"
int main(void)
{
	mode_t mode = S_IRUSR|S_IWUSR|S_IXUSR;
	DIR *dir;
	struct dirent *direntp;

	Mkdir(DIRNAME, mode);
	system ("ls -l ");
	dir = Opendir(DIRNAME);
	while(direntp = readdir(dir))
	{
		
	}
	Closedir(dir);

	Rmdir(DIRNAME);
	system ("ls -l ");
	return 0;
}
