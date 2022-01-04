#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
struct stats
{
	float ass1[817];
	float ass2[817];
	float ass3[817];
	float ass4[817];
	float ass5[817];
	float ass6[817];
};
struct pair
{
	int f;
	int s;
};
void average(float arr[],int size)
{
    float sum=0;
    for(int i=1;i<=size;i++)
	{
        sum=sum+arr[i-1];
    }
    float avg=sum/size;
    printf("%f	",avg);
}
void cal_average(struct stats* temp,int size)
{
	average(temp->ass1,size);
	average(temp->ass2,size);
	average(temp->ass3,size);
	average(temp->ass4,size);
	average(temp->ass5,size);
	average(temp->ass6,size);
	printf("\n");
}
int number_of_commas=0;
void solve(char buff[],char section,int size)
{
	const char comma_char[2]=",";
	char* token=strtok(buff,comma_char);
	struct stats* st=(struct stats*)malloc(sizeof(struct stats));
	int row=0;
	while(1)
	{
		if(token==NULL)
		{
			break;
		}
		if(*token!=section)
		{
			token=strtok(NULL,comma_char);
			continue;
		}
		else
		{
			token=strtok(NULL,comma_char);
			st->ass1[row]=atoi(token);
			token=strtok(NULL,comma_char);
			st->ass2[row]=atoi(token);
			token=strtok(NULL,comma_char);
			st->ass3[row]=atoi(token);
			token=strtok(NULL,comma_char);
			st->ass4[row]=atoi(token);
			token=strtok(NULL,comma_char);
			st->ass5[row]=atoi(token);
			token=strtok(NULL,comma_char);
			st->ass6[row]=atoi(token);
			row++;
		}
	}
	printf("Average of section %c is : ",section);
	cal_average(st,size);
}
int open_and_cal_size()
{
    int open_id=open("student_record.csv",O_RDONLY);
    int size=lseek(open_id,0,SEEK_END);
    close(open_id);
	return size;
}
struct pair* cal_commas(int size)
{
	int open_id=open("student_record.csv",O_RDONLY);
	struct pair* p=(struct pair*)malloc(sizeof(struct pair)*1);
	char buff[size];
	int pointer=0;
	while(1)
	{
		if(read(open_id,buff,1)==0) break;
        lseek(open_id,pointer,SEEK_SET);
        read(open_id,&buff[pointer],1);
        if(buff[pointer]==',')
		{
            number_of_commas++;
        }
        if(buff[pointer]=='\n') { break;}
        pointer++;
    }
	close(open_id);
	p->f=number_of_commas;
	p->s=pointer;
	return p;
}
char* preare_and_load_file(int length_to_prepare)
{
	char* buffer=(char*)malloc(sizeof(char)*length_to_prepare);
	int initial=0;
	int middle=96;
    int open_id=open("student_record.csv",O_RDONLY);
    while(read(open_id,buffer,1)!=0)
	{
		if(read(open_id,buffer,1)==0) break;
        lseek(open_id,middle,SEEK_SET);
		middle++;
        read(open_id,&buffer[initial],1);
        initial++;
    }
	return buffer;
}
struct pair* cal_A_b(char buffer[],int size)
{
	struct pair* p=(struct pair*)malloc(sizeof(struct pair)*1);
	int num_A=0,num_B=0;
	for(int k=0;k<size;k++)
	{
        if(buffer[k]=='A')
		{
            num_A++;
        }
        else if(buffer[k]=='B')
		{
            num_B++;
        }
    }
	p->f=num_A;
	p->s=num_B;
	return p;
}
int main()
{
    int pid;
    int current;
    pid=fork();
	int size_of_file=open_and_cal_size();
	struct pair* temp=cal_commas(size_of_file);
	char* buffer=preare_and_load_file(size_of_file-temp->s);
	struct pair *p=cal_A_b(buffer,size_of_file-temp->s+1);
    if(pid<0)
    {
        printf("Child process forking is unsuccessful\n");
        return 0;
    }
    if(pid==0)
    {
        solve(buffer,'A',p->f);
        exit(0);
    }
    else
    {
        waitpid(pid,&current,0);
        solve(buffer,'B',p->s);
        exit(0);
    }
	return 0;
}
