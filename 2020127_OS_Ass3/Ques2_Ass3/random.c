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

struct data *generate_random_string()
{
    int i,j,k;
    char ch;
    struct data *d=(struct data *)malloc(sizeof(struct data)*1);
    for(i=0;i<50;i++)
    {
        for(j=0;j<3;j++)
        {
            d->arr[i][j]=(char)(rand()%26+97);
        }
    }
    return d;
}

void print_all_strings(struct data *d)
{
	int i,j,k;
	for(i=0;i<50;i++)
	{
		for(j=0;j<3;j++)
		{
			printf("%c",d->arr[i][j]);
		}
		printf("\n");
	}
}
int main()
{
	struct data *d=generate_random_string();
	printf("Strings are as follows: \n");
	print_all_strings(d);
    struct msg_buffer buff_struct;
    buff_struct.msg=1;
    key_t key;
    int msgid,msgid1;
	sender_struct.msg=1;
    key_t key1;
    int len_of_str=5;
	d->firstidx = 50;
	d->secondidx=3;
	for(int i=0;i<50;)
	{
		key = ftok("random.c", proj_id);
    	msgid = msgget(key, msgflg | IPC_CREAT);
		for (int j = 0; j <len_of_str;)
		{
			int curr_pos=i+j;
			for(int k=0;k<d->secondidx;)
			{
				buff_struct.arr[j][k]=d->arr[curr_pos][k];
				k++;
			}
			buff_struct.id[j]=curr_pos;
			j++;
		}
		msgsnd(msgid, &buff_struct, sizeof(buff_struct), 0);
		key1 = ftok("receiver.c", proj_id);
		msgid1 = msgget(key1, msgflg | IPC_CREAT);
        msgrcv(msgid1 , &sender_struct , sizeof(sender_struct), 1, 0);
		printf("Index: %d\n" , sender_struct.pos);
		sleep(fixed_time);
		i+=5;
	}
	msgctl(msgid1,IPC_RMID,0);
    return 0;
}