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
#include<time.h>
#include<sys/resource.h>
#include<sys/mman.h>
#include<sys/shm.h>
#include<math.h>
#define SIGTERM 15
static __inline__ unsigned long long Rdtsc(void)
{
    unsigned r,l;
    __asm__ __volatile__ ("rdtsc" : "=a"(l), "=d"(r));
    uint64_t num;
    num=((unsigned long long)l) | (((unsigned long long)r)<<32);
    return num;
}
int power(int x,int y)
{
    int res = 1;
    while (y > 0)
    {
        if (y & 1)
            res = res*x;
        y = y>>1;
        x = x*x;
    }
    return res;
}
void generator(int len, siginfo_t *siginfo, void *v)
{
    uint64_t a=Rdtsc();
    sleep(4);

    uint64_t num=a/CLOCKS_PER_SEC;
	for(int i=0;i<3;i++)
	{
		num=num/(power(10,1));
	}
    int res=365;
    printf("\nyears:%d",(num)/(res*60*60*24));
    res=31;
    printf("\nmonths:%d",(num)/((--res)*60*60*24));
    printf("\ndays:%d",((num)/(60*60*24))-((num)/(60*60*24)));
    printf("\nhours:%d",num/(60*60));
    printf("\nminutes:%d",(num%(60*60))/60);
    int val=num%(60*60);
    printf("\nseconds:%d\n",val%60);
    
    fflush(stdout);
    printf("CPU Time Stamp received from Rdtsc: %llu\n",a);

    union sigval usi;
    usi.sival_ptr = (void(*)(int))a;

    sigqueue(siginfo->si_value.sival_int,SIGTERM,usi);
    kill(siginfo->si_value.sival_int,SIGTERM);
}

int main(int argc, char* argv[])
{
    struct sigaction sigtion;
    int pids=atoi(argv[0]);

    sigtion.sa_flags = SA_SIGINFO;
    sigtion.sa_sigaction = &generator;

    sigaction(SIGALRM, &sigtion, NULL);
    
    union sigval val;
    val.sival_int = pids;

    int it=1;
    while(it)
    {
        sigqueue(getpid(), SIGALRM, val);
    }

    struct itimerval timer;
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = 500000;
    timer.it_interval = timer.it_value;
    setitimer(ITIMER_REAL, &timer, NULL);

    return 0;

}
