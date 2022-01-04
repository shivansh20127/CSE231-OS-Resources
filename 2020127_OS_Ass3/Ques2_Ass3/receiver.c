#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<string.h>
#include<sys/types.h>
#include<signal.h>
#include<time.h>
#include<unistd.h>
#include<sys/time.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#define proj_id 65
#define msgflg 0666
#define fixed_time 1
struct msg_buffer 
{
    long int msg;
    char arr[5][3];
    int id[5];
} buff_struct;

struct data 
{
	char arr[50][3];
	int firstidx;
	int secondidx;
};

struct msg_rcv 
{
    long int msg;
	int pos;
} sender_struct;
  

int main()
{
    buff_struct.msg = 1;
    key_t key;
    int msgid1;
    key = ftok("random.c",proj_id);
    int msgid;
	struct data *d=(struct data*)malloc(sizeof(struct data)*1);
	int len_of_str=5;
	d->firstidx = 50;
	d->secondidx=3;
    for(int i = 0; i<d->firstidx;)
	{
        msgid = msgget(key, msgflg | IPC_CREAT);
        msgrcv(msgid,&buff_struct,sizeof(buff_struct),1,0);
        int id;
        int j = 0;
        for (j =0;j<len_of_str;)
		{
			for(int k=0;k<d->secondidx;)
			{
                printf("%c", buff_struct.arr[j][k]);
				k++;
            }
            printf("\n");
            id = buff_struct.id[j];
            printf("Index: %d\n" , id);
			j++;
        }
		sleep(fixed_time);
        sender_struct.pos= id;
        key_t key1 = ftok("receiver.c",proj_id);
        sender_struct.msg = 1;
        msgid1 = msgget(key1, msgflg | IPC_CREAT);
        msgsnd(msgid1, &sender_struct, sizeof(sender_struct), 0);
		i+=5;
    }
    msgctl(msgid,IPC_RMID,0);
	return 0;
}