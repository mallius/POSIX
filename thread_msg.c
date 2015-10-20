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

pthread_t tid;
Message msg_snd;
Message msg_rcv;
key_t key;
int msg_id;


void *MsgSend(void *arg)
{
	int ret;
	ret = msgsnd(msg_id, (Message *)arg, sizeof(arg), IPC_NOWAIT);
	if(ret == -1)
	{
		fprintf(stdout, "msgsnd error[%s]\n", strerror(errno));
		return NULL;
	}
		
	return NULL;
}

int main(void)
{
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
	memset(&msg_snd, 0, sizeof(msg_snd));
	strcpy(msg_snd.message, "Marry");
	ret = pthread_create(&tid, NULL, MsgSend, &msg_snd);
	if(ret)
	{
		fprintf(stderr, "pthread_create error\n");
		return ret;
	}

	ret = pthread_join(tid, NULL);
	if(ret)
	{
		fprintf(stderr, "pthread_join error\n");
		return ret;
	}


	Message msg_rcv;
	memset(&msg_rcv, 0, sizeof(msg_rcv));
	/* 从指定的消息队列接收消息1 */
	ret = msgrcv(msg_id, &msg_rcv, sizeof(msg_rcv), 0, IPC_NOWAIT);
	if(ret == -1)
	{
		fprintf(stderr, "msgrcv error[%s]\n", strerror(errno));
	}
	fprintf(stdout, "msg_rcv:[%s]\n", msg_rcv);

	/* 从指定的消息队列接收消息2 */
	memset(&msg_rcv, 0, sizeof(msg_rcv));
	ret = msgrcv(msg_id, &msg_rcv, sizeof(msg_rcv), 0, IPC_NOWAIT);
	if(ret == -1)
	{
		fprintf(stderr, "msgrcv error[%s]\n", strerror(errno));
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
