#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(void)
{
	pthread_rwlockattr_t attr;
	pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER; /* 读写锁初始化 */
	int ret;
	/* 初始化读写锁 */
	ret = pthread_rwlockattr_init(&attr);
	if(ret)
	{
		fprintf(stderr, "pthread_rwlock_init error.\n");
		return ret;
	}
	/* 设置读写锁属性 */
	ret = pthread_rwlockattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
	if(ret)
	{
		fprintf(stderr, "pthread_rwlockattr_setpshared error.\n");
		return ret;
	}

	/* 获取读写锁属性 */
	int pshared;
	ret = pthread_rwlockattr_getpshared(&attr, &pshared);
	if(ret)
	{
		fprintf(stderr, "pthread_rwlockattr_getpshared error.\n");
		return ret;
	}
	fprintf(stdout, "读写锁属性pshared:[%d]\n", pshared);

	/* 初始化读写锁 */
	ret = pthread_rwlock_init(&rwlock, &attr);
	if(ret)
	{
		fprintf(stderr, "pthread_rwlock_init error.\n");
		return ret;
	}

	/* 获取读写锁中的读锁 */
	ret = pthread_rwlock_rdlock(&rwlock);
	if(ret)
	{
		fprintf(stderr, "pthread_rwlock_rdlock error.\n");
		return ret;
	}

	/* 解除锁定读写锁 */
	ret = pthread_rwlock_unlock(&rwlock);
	if(ret)
	{
		fprintf(stderr, "pthread_rwlock_unlock error.\n");
		return ret;
	}

	/* 读取非阻塞读写锁中的锁 */
	ret = pthread_rwlock_tryrdlock(&rwlock);
	if(ret)
	{
		fprintf(stderr, "pthread_rwlock_tryrdlock error.\n");
		return ret;
	}

	/* 解除 */
	ret = pthread_rwlock_unlock(&rwlock);
	if(ret)
	{
		fprintf(stderr, "pthread_rwlock_unlock error[%s]\n", strerror(errno));
		return ret;
	}	

	/* 写入读写锁中的锁 */
	ret = pthread_rwlock_wrlock(&rwlock);
	if(ret)
	{
		fprintf(stderr, "pthread_rwlock_rwlock error[%s]\n", strerror(errno));
		return ret;
	}

	/* 解除 */
	ret = pthread_rwlock_unlock(&rwlock);
	if(ret)
	{
		fprintf(stderr, "pthread_rwlock_unlock error[%s]\n", strerror(errno));
		return ret;
	}	

	/* 写入非阻塞读写锁中的锁 */
	ret = pthread_rwlock_trywrlock(&rwlock);
	if(ret)
	{
		fprintf(stderr, "pthread_rwlock_trywrlock error[%s]\n", strerror(errno));
		return ret;
	}
	
	/* 解除 */
	ret = pthread_rwlock_unlock(&rwlock);
	if(ret)
	{
		fprintf(stderr, "pthread_rwlock_unlock error[%s]\n", strerror(errno));
		return ret;
	}	

	/* 销毁读写锁 */
	ret = pthread_rwlockattr_destroy(&attr);
	if(ret)
	{
		fprintf(stderr, "pthread_rwlockattr_destroy.\n");
		return ret;
	}

	ret = pthread_rwlock_destroy(&rwlock);
	if(ret)
	{
		fprintf(stderr, "pthread_rwlock_destroy error.\n");
		return ret;
	}

	return 0;
}
