#include <stdio.h>
#include <string.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

typedef struct msg_buf{
	char msg[1024];
} Message;

int main(void)
{
	mqd_t mqdes;
	Message msg_snd;
	Message msg_rcv;
	int ret;
	int prio;

	mqdes = mq_open("/tmp", O_CREAT|O_EXCL, S_IRUSR, NULL);
	//mqdes = mq_open("/tmp", O_WRONLY);
	if(mqdes == -1)
	{
		fprintf(stderr, "mq_open error[%s]\n", strerror(errno));
	}

#if 1
	memset(&msg_snd, 0, sizeof(msg_snd));
	strcpy(msg_snd.msg, "John");
	prio = 1;
	mqdes = mq_send(mqdes, msg_snd.msg, sizeof(msg_snd), prio);
	if(mqdes == -1)
	{
		fprintf(stderr, "mq_snd error[%s]\n", strerror(errno));
	}
#endif

	ret = mq_close(mqdes);
	if(ret == -1)
	{
		fprintf(stderr, "mq_close error[%s]\n", strerror(errno));
	}

	mqdes = mq_unlink("/tmp");
	if(ret == -1)
	{
		fprintf(stderr, "mq_unlink error[%s]\n", strerror(errno));
	}
	return 0;
}
