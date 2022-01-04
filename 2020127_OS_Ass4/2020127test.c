#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
#include <sys/syscall.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>
#include <sys/types.h>
#define pshared 0
#define value 1
sem_t forkk;
struct data
{
    char buffer[8];
};
int main()
{
    sem_init(&forkk,pshared,value);
    pid_t pid = fork();
    int i=1;
    while(i>0)
    {
        if(pid<0) 
        {
            printf("fork error\n");

        }
        else if(pid == 0)
        {
            struct data *d=(struct data *)malloc(sizeof(struct data)*1);
            sem_wait(&forkk);
            syscall(450,d->buffer);
            printf("Bytes read are %s and data in queue is %s\n",d->buffer,d->buffer);
            fflush(stdout);
            sem_post(&forkk);
            sleep(value);
        }
        else
        {    
            int fd = open("/dev/urandom", O_RDONLY);
            struct data *d=(struct data *)malloc(sizeof(struct data)*1);
            read(fd,d->buffer, sizeof(d->buffer));
            close(fd);
            sem_wait(&forkk);
            syscall(449,d->buffer);
            printf("Write data is %d and data in queue is %s\n",d->buffer,d->buffer);
            fflush(stdout);
            sem_post(&forkk);
            sleep(value);
        }
    }
}