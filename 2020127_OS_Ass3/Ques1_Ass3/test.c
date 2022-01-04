#include<string.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#define MOD (int)(1e9)+7 
#define int long long
#define big_num 1e7
clock_t getclock()
{
    return clock();
}
int main()
{
    pid_t p=fork();
    if(p<0)
    {
        printf("Fork failed\n");
        return 0;
    }
    else
    {
        if(p==0)
        {
            clock_t t = getclock();
            for(int i=0; i<big_num;){i++;};
            t-= getclock();
            t=abs(t);
            double time_taken = (t*2.0)/CLOCKS_PER_SEC;
            fflush(stdout);
            printf("Time taken by child process: %f\n",time_taken);
            fflush(stdout);
            return 0;
        }
        else
        {
            clock_t t = clock();
            syscall(449,p,MOD);
            for(int i=0; i<big_num;){i++;};
            t-= getclock();
            t=abs(t);
            double time_taken =(t*2.0)/CLOCKS_PER_SEC;
            fflush(stdout);
            printf("Time taken by parent process: %f\n",time_taken);
            fflush(stdout);
            return 0;
        }
    }
    return 0;
}
