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
sem_t forkk[fixed_size];
struct data
{
	int id;
	int left;
	int right;
	pid_t pid;
};
void* helper(int i) 
{
    if(i%4==0 && i!=0)
    {
        sem_wait(&forkk[0]);
        sem_wait(&forkk[4]);
    }
    else
    {
        sem_wait(&forkk[i]);
        sem_wait(&forkk[i+1]);
    }
	struct data *d = (struct data*)malloc(sizeof(struct data)*1);
	d->id = i;
	d->left = i;
	d->right = i+1;
	sleep(1);
    printf("Philosopher number %d ",i);
	printf("has selected forks %d and %d\n",i,(i+1)%5);
	fflush(stdout);
   	if(i%4==0 && i!=0)
    {
        sem_post(&forkk[0]);
        sem_post(&forkk[4]);
    }
    else
    {
        sem_post(&forkk[i]);
        sem_post(&forkk[i+1]);
    }
}
int main(int argc, char *argv[]) 
{
    struct roundtable *rtable = (struct roundtable*)malloc(sizeof(struct roundtable)*1);
    for(int i = 0; i<fixed_size; i++) sem_init((&(forkk[i%fixed_size])), pshared,value);
	while(1)
	{
		for(int i = 0; i<fixed_size; i++)
		{
			pthread_create(&(rtable->th[i]), NULL, &helper, i);
		}
		for(int i = 0; i<fixed_size; i++)
		{
			pthread_join(rtable->th[i], NULL);
		}
		printf("**************************\n");
	}
	return 0;
}
