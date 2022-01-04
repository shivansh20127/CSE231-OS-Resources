#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <semaphore.h>

sem_t forks[5];
sem_t bowel[5];

void* philospher(int i) 
{
	int temp=i;
    sem_wait(&forks[i]);
    sem_wait(&bowel);
    sem_getvalue(&bowel, &temp);
	printf("Philosopher %d is having %d bowl and %d fork\n", i,temp,i);
    sem_post(&forks[i]);
	sem_post(&bowel);
}

int main(int argc, char *argv[]) 
{
	pthread_t th1,th2,th3,th4,th5;
	sem_init(&forks[0], 0, 1);
	sem_init(&forks[1], 0, 1);
	sem_init(&forks[2], 0, 1);
	sem_init(&forks[3], 0, 1);
	sem_init(&forks[4], 0, 1);
	sem_init(&bowel, 0, 4);
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