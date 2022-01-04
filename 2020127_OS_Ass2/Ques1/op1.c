#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>
#include<sys/msg.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<inttypes.h>
#include<sys/time.h>
#include<sys/resource.h>
#include<sys/mman.h>
#include<sys/shm.h>
#define SIGTERM 15
int getrandom(uint64_t *receiver)
{
	unsigned char flag;
	asm volatile ("rdrand %0; setc %1" : "=r" (*receiver), "=qm" (flag));
	return (int) flag;
}
void generator(int n, siginfo_t* siginfo, void* v)
{
    sleep(4);
    uint64_t num;
    int error_no=getrandom(&num);
    if(error_no==0)
    {
        printf("No Number generated\n");
    }
    printf("Number generated with rdrand: %llu\n", num);
    union sigval val;
    val.sival_ptr=(void(*)(int))num;
    sigqueue(siginfo->si_value.sival_int,SIGTERM,val);
	kill(siginfo->si_value.sival_int,SIGTERM);
}
int main(int argc, char* argv[])
{
	struct sigaction sigtion;
    int pids=atoi(argv[0]);

    sigtion.sa_flags = SA_SIGINFO;
    sigtion.sa_sigaction = &generator;

    union sigval val;
    val.sival_int = pids;

	int it=1;
    while(it)
    {
        sigaction(SIGALRM, &sigtion, NULL);
        sigqueue(getpid(), SIGALRM, val);
    }
    struct itimerval timer;
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = 500000;
    timer.it_interval = timer.it_value;
    setitimer(ITIMER_REAL, &timer, NULL);

    return 0;
}
