#include <pthread.h>
#include <stdio.h>

pthread_condattr_t cattr;
int ret;

pthread_cond_t cv;

int main(void)
{
	/* 初始化条件变量属性 */
	ret = pthread_condattr_init(&cattr);
	if(ret)
	{
		fprintf(stderr, "pthread_condattr_init error.\n");
		return ret;
	}
	/* 设置条件变量的范围 */
	ret = pthread_condattr_setpshared(&cattr, PTHREAD_PROCESS_SHARED);
	if(ret)
	{
		fprintf(stderr, "pthread_condattr_setpshared error.\n");
		return ret;
	}
	
	/* 初始化条件变量 */
	ret = pthread_cond_init(&cv, &cattr);
	if(ret)
	{
		fprintf(stdout, "pthread_cond_init error.\n");
		return ret;	
	}

	/* 获取条件变量的范围 */
	int pshared;
	ret = pthread_condattr_getpshared(&cattr, &pshared);
	if(ret)
	{
		fprintf(stderr, "pthread_condattr_getshared error.\n");
		return ret;
	}
	fprintf(stdout, "条件变量范围：[%d]\n", pshared);

	/* 删除条件变量属性 */
	ret = pthread_condattr_destroy(&cattr);
	if(ret)
	{
		fprintf(stderr, "pthread_condattr_error.\n");
		return ret;
	}
	return 0;
}
