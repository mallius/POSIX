LIB= -lpthread -L. -lWrapper
LRT= -lrt
PROGS = key_create \
	self \
	setschedparam \
	attr_init \
	attr_setdetachstate \
	attr_setguardsize \
	mutexattr \
	mutex_init \
	condattr_init \
	cond_wait \
	sem \
	prod \
	rwlockattr \
	messageQue \
	thread_msgQue \
	rwlock_producer_consumer \
	sem_open \
	mq_open \
	01producers_consumer \
	02producers_consumer \
	sig

all: pthread_key_create.c \
	pthread_self.c \
	pthread_setschedparam.c \
	pthread_attr_init.c \
	pthread_attr_setdetachstate.c \
	pthread_attr_setguardsize.c \
	pthread_mutexattr_init.c \
	pthread_mutex_init.c \
	pthread_condattr_init.c \
	pthread_cond_wait.c \
	sem_init.c \
	sem_producer.c \
	pthread_rwlockattr_init.c \
	msg.c \
	thread_msg.c \
	rwlock_producer_consumer.c \
	sem_open.c \
	mq_open.c \
	01pthread_mutex_producers_consumer.c \
	02pthread_mutex_producers_consumer.c \
	sig.c
	gcc pthread_key_create.c -o key_create -lpthread
	gcc pthread_self.c -o self -lpthread
	gcc pthread_setschedparam.c -o setschedparam $(LIB)
	gcc pthread_attr_init.c -o attr_init $(LIB)
	gcc pthread_attr_setdetachstate.c -o attr_setdetachstate $(LIB)
	gcc pthread_attr_setguardsize.c -o attr_setguardsize $(LIB)
	gcc pthread_mutexattr_init.c -o mutexattr $(LIB)
	gcc pthread_mutex_init.c -o mutex_init $(LIB)
	gcc pthread_condattr_init.c -o condattr_init $(LIB)
	gcc pthread_cond_wait.c -o cond_wait $(LIB)
	gcc sem_init.c -o sem $(LIB)
	gcc sem_producer.c -o prod $(LIB)
	gcc pthread_rwlockattr_init.c -o rwlockattr $(LIB)
	gcc msg.c -o messageQue $(LIB)
	gcc thread_msg.c -o thread_msgQue $(LIB)
	gcc rwlock_producer_consumer.c -o rwlock_producer_consumer $(LIB)
	gcc sem_open.c -o sem_open $(LIB)
	gcc mq_open.c -o mq_open $(LRT)
	gcc 01pthread_mutex_producers_consumer.c -o 01producers_consumer $(LIB)
	gcc 02pthread_mutex_producers_consumer.c -o 02producers_consumer $(LIB)
	gcc sig.c -o sig

.PHONY:clean
clean:
	$(RM) $(PROGS) core*
