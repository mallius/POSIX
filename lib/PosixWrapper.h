#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int Pthread_create(pthread_t *tid, const pthread_attr_t *attr, void *(*func)(void *), void *arg);
int Pthread_join(pthread_t tid, void **status);
int Pthread_mutex_lock(pthread_mutex_t *mtex);
int Pthread_mutex_unlock(pthread_mutex_t *mptex);
