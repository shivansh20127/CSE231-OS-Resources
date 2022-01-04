#include <string.h>
#include <time.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#define fixed_size 5
#define pshared 0
#define value 1
struct roundtable
{
    pthread_t th[fixed_size];
};
struct data
{
	int id;
	int fork;
	int bowl;
	pid_t pid;
};
sem_t forkk[fixed_size];
sem_t bowl[fixed_size];

void* helper(int i) 
{
    sem_wait(&forkk[i]);
    sem_wait(&bowl);
	struct data *d = (struct data*)malloc(sizeof(struct data)*1);
	d->id = i;
	d->fork = i;
	sem_getvalue(&bowl,&d->bowl);
	sleep(1);
	printf("Philosopher number %d ",i);
	printf("has selected fork %d ",i);
	printf("and bowl number %d\n",d->bowl);
	fflush(stdout);
	sem_post(&bowl);
	sem_post(&forkk[i]);
}
int main() 
{
	struct roundtable *r = (struct roundtable*)malloc(sizeof(struct roundtable)*1);
	for(int i=0;i<fixed_size;i++) sem_init(&forkk[i%fixed_size], pshared, value);
	sem_init(&bowl, pshared,fixed_size-1);
	while(1)
	{
		for(int i = 0; i<fixed_size; i++)
		{
			pthread_create(&(r->th[i]), NULL,&helper, i);
		}
		for(int i = 0; i<fixed_size; i++)
		{
			pthread_join(r->th[i], NULL);
		}
		printf("**************************\n");
	}
	return 0;
}