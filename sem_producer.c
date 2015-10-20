#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

sem_t sem;
sem_t sem_consumer;
int cnt = 1;
int food = 0;

void producer(void)
{
	fprintf(stdout, "producer线程.\n");
	while(1)
	{
		sem_wait(&sem_consumer);
		food = food + 1;
		fprintf(stdout, "prod:[%d]\n", food);
		sem_post(&sem);
	}	
	return ;
}
void consumer(void)
{
	fprintf(stdout, "consumer线程.\n");
	while(1)
	{
		sem_wait(&sem);
		food--;
		fprintf(stdout, "consume:[%d]\n", food);
		sleep(1);
		sem_post(&sem_consumer);
	}
	return ;
}
int main(void)
{
	int ret;
	pthread_t tid1;
	pthread_t tid2;

	ret = sem_init(&sem, 0, cnt);
	if(ret)
	{
		fprintf(stdout, "sem_init error.\n");
		return ret;
	}

	ret = sem_init(&sem_consumer, 0, cnt);
	if(ret)
	{
		fprintf(stderr, "sem_init sem_consumrer error.\n");
		return ret;
	}
	
	
	ret = pthread_create(&tid1, NULL, producer, NULL);
	if(ret)
	{
		fprintf(stderr, "pthread_create tid1 error.\n");
		return ret;
	}
	
	ret = pthread_create(&tid2, NULL, consumer, NULL);
	if(ret)
	{
		fprintf(stderr, "pthread_create tid2 error.\n");
		return ret;
	}
	

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	ret = sem_destroy(&sem);
	if(ret)
	{
		fprintf(stdout, "sem_destroy error.\n");
		return ret;
	}

	ret = sem_destroy(&sem_consumer);
	if(ret)
	{
		fprintf(stderr, "sem_destroy error.\n");
		return ret;
	}


	fprintf(stdout, "PROCESS OK");
	return 0;
}
