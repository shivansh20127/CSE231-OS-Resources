#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <semaphore.h>

sem_t forks[5];

void* philospher(int i)
{
    if(i == 4)
    {
        sem_wait(&forks[0]);
        sem_wait(&forks[4]);
    }
    else if(i==0 || i==1 || i==2 || i==3)
    {
        sem_wait(&forks[i]);
        sem_wait(&forks[i+1]);
    }
    printf("Philosopher %d is having %d and %d\n", i, i,i+1);
    if(i == 4)
    {
        sem_post(&forks[0]);
        sem_post(&forks[4]);
    }
    else if(i==0 || i==1 || i==2 || i==3)
    {
        sem_post(&forks[i]);
        sem_post(&forks[i+1]);
    }
}
int main() 
{
    pthread_t th1,th2,th3,th4,th5;
	sem_init(&forks[0], 0, 1);
	sem_init(&forks[1], 0, 1);
	sem_init(&forks[2], 0, 1);
	sem_init(&forks[3], 0, 1);
	sem_init(&forks[4], 0, 1);
    while(1)
    {
		pthread_create(&th1, NULL, &philospher,0);
		pthread_create(&th2, NULL, &philospher,1);
		pthread_create(&th3, NULL, &philospher,2);
		pthread_create(&th4, NULL, &philospher,3);
		pthread_create(&th5, NULL, &philospher,4);

		pthread_join(th1, NULL);
		pthread_join(th2, NULL);
		pthread_join(th3, NULL);
		pthread_join(th4, NULL);
		pthread_join(th5, NULL);
		printf("\n");
    }
    return 0;
}