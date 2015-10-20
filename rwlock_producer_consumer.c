#include <pthread.h>
#include <fcntl.h>
#include <sys/mman.h>

typedef struct _buffer{

	int occupied;
	int nextin;
	int nextout;
} buffer_t;

int main(void)
{
	int zfd;
	buffer_t *buffer;
	pthread_mutexattr_t mattr;
	pthread_condattr_t cvattr_less, cvattr_more;

	zfd = open("/dev/zero", O_RDWR);
	buffer = (buffer_t *)mmap(NULL, sizeof(buffer_t), PROT_READ|PROT_WRITE, MAP_SHARED, zfd, 0);
	buffer->occupied = buffer->nextin = buffer->nextout = 0;

	pthread_mutexattr_init(&mattr);
	pthread_mutexattr_setpshared(&mattr, PTHREAD_PROCESS_SHARED);


}
