#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<errno.h>
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
struct sec_data
{
    char section;
    float average[6];
};
int number_of_commas=0;
float average(float arr[],int size)
{
    float sum=0;
    for(int i=1;i<=size;i++)
	{
        sum=sum+arr[i-1];
    }
    float avg=sum/size;
    printf("%f	",avg);
	return sum;
}
void cal_average(struct stats* temp,int size,struct sec_data* pointer)
{
	float ans1=average(temp->ass1,size);
	float ans2=average(temp->ass2,size);
	float ans3=average(temp->ass3,size);
	float ans4=average(temp->ass4,size);
	float ans5=average(temp->ass5,size);
	float ans6=average(temp->ass6,size);
	pointer->average[0]=ans1;
	pointer->average[1]=ans2;
	pointer->average[2]=ans3;
	pointer->average[3]=ans4;
	pointer->average[4]=ans5;
	pointer->average[5]=ans6;
	printf("\n");
}
void solve(char buff[],char section,int size,struct sec_data* to_fill)
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
	cal_average(st,size,to_fill);
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
int open_and_cal_size()
{
    int open_id=open("student_record.csv",O_RDONLY);
    int size=lseek(open_id,0,SEEK_END);
    close(open_id);
	return size;
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
void* enter(struct sec_data* chosen)
{
    int size_of_file=open_and_cal_size();
	struct pair* temp=cal_commas(size_of_file);
	char* buffer=preare_and_load_file(size_of_file-temp->s);
	struct pair *p=cal_A_b(buffer,size_of_file-temp->s+1);
	if(chosen->section=='A') solve(buffer,chosen->section,p->f,chosen);
	else if(chosen->section=='B') solve(buffer,chosen->section,p->s,chosen);
    printf("\n");
}
int main()
{
    struct sec_data* sec_a=(struct sec_data*)malloc(sizeof(struct sec_data)*1);
    sec_a->section='A';
    memset(sec_a->average,0,sizeof(sec_a->average));
    struct sec_data* sec_b=(struct sec_data*)malloc(sizeof(struct sec_data)*1);
    sec_b->section='B';
    memset(sec_b->average,0,sizeof(sec_b->average));
	int create,ret;
    pthread_t thread1,thread2;
    create=pthread_create(&thread1,NULL,enter, (struct sec_data*)sec_a);
	if(create) 
	{
		printf("Thread is not created !\n");
		exit(EXIT_FAILURE);
    }
	ret=pthread_join(thread1,NULL);
	if(ret)
	{
		printf("Thread is not joined !\n");
		exit(EXIT_FAILURE);
	}
    create=pthread_create(&thread2,NULL,enter, (struct sec_data*)sec_b);
	if(create) 
	{
		printf("Thread is not created !\n");
		exit(EXIT_FAILURE);
    }
    ret=pthread_join(thread2,NULL);
	if(ret)
	{
		printf("Thread is not joined !\n");
		exit(EXIT_FAILURE);
	}
	for(int i=0;i<6;i++)
	{
    	printf("Average of section A and B for assignment %d is : ",i+1);
		printf("%f\n",(sec_a->average[i]+sec_b->average[i])/26);
	}
}