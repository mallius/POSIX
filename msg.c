#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <sys/msg.h>
#include <string.h>
#include <errno.h>
#define KEY_PATH "./"

typedef struct msg_buf{
	char message[1024];
} Message;

int main(void)
{
	key_t key;
	int msg_id;
	int ret;
	
	Message msg_buf;

	/* 创建key */
	key = ftok(KEY_PATH, 'a');
	if(key == -1)
	{
		fprintf(stderr, "ftok erro.\n");
		return -1;
	}

	/* 获取标识符 */
	msg_id = msgget(key, IPC_CREAT|0600);
	if(msg_id == -1)
	{
		fprintf(stderr, "msgget error[%s]\n", strerror(errno));
		return -1;
	}
	fprintf(stdout, "msg_id:[%d]\n", msg_id);
	
	/* 向指定的消息队列发送消息1 */
	memset(&msg_buf, 0, sizeof(msg_buf));
	strcpy(msg_buf.message, "John");
	ret = msgsnd(msg_id, &msg_buf, sizeof(msg_buf), IPC_NOWAIT);
	if(ret == -1)
	{
		fprintf(stderr, "msgsnd error[%s]\n", strerror(errno));
		return -1;
	}

	/* 向指定的消息队列发送消息2 */
	memset(&msg_buf, 0, sizeof(msg_buf));
	strcpy(msg_buf.message, "Peter");
	ret = msgsnd(msg_id, &msg_buf, sizeof(msg_buf), IPC_NOWAIT);
	if(ret == -1)
	{
		fprintf(stderr, "msgsnd error[%s]\n", strerror(errno));
		return -1;
	}

	Message msg_rcv;
	memset(&msg_rcv, 0, sizeof(msg_rcv));
	/* 从指定的消息队列接收消息1 */
	ret = msgrcv(msg_id, &msg_rcv, sizeof(msg_rcv), 0, IPC_NOWAIT); /* type为0 */
	if(ret == -1)
	{
		fprintf(stderr, "msgrcv error[%s]\n", strerror(errno));
		return -1;
	}
	fprintf(stdout, "msg_rcv:[%s]\n", msg_rcv);

	memset(&msg_rcv, 0, sizeof(msg_rcv));
	ret = msgrcv(msg_id, &msg_rcv, sizeof(msg_rcv), 0, IPC_NOWAIT);
	if(ret == -1)
	{
		fprintf(stderr, "msgrcv error[%s]\n", strerror(errno));
		return -1;
	}
	fprintf(stdout, "msg_rcv:[%s]\n", msg_rcv);


	/* 删除消息队列 */
	ret = msgctl(msg_id, IPC_RMID, NULL);
	if(ret == -1)
	{
		fprintf(stderr, "msgctl err[%s]\n", strerror(errno));
		return -1;
	}
	fprintf(stdout, "删除msg_id[%d]\n", msg_id);
	
	return 0;
}
