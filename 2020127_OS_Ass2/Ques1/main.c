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
void sighandler(int n, siginfo_t *para, void *v)
{
    uint64_t* uin;
    uin= para->si_value.sival_ptr;
    if(uin==NULL)
    {
        printf("No Number Received\n");
    }
    else
    {
        printf("Number received in S1 - %llu\n",uin);
    }
}

int main()
{
    int process_id;
    process_id=fork();
    if(process_id == 0)
    {
        struct sigaction sig_action;
        sig_action.sa_sigaction = &sighandler;
        sig_action.sa_flags = SA_SIGINFO;
        while(1)
        {
            sigaction(SIGTERM, &sig_action, NULL);
            sleep(1);
        }
    }
    else if(process_id>0)
    {
        int Rpid,Tpid;
        char text[20];
        sprintf(text, "%d", process_id);
        (Rpid= fork()) && (Tpid= fork());
        if(Rpid== 0) execlp("./op1", text, "NULL");
        else if(Tpid== 0) execlp("./op2", text, "NULL");
    }
    return 0;
}
