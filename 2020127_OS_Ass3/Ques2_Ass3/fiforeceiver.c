#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<errno.h>
#include<fcntl.h>

char arr[50][5];

struct mesg {
    int return_index;
    char text[10];
    int index;
} message[5];

void sendIndex(int i){
    int fd;
    fd = open("temp", O_WRONLY);
    int index = i + 4;
    write(fd, &index, sizeof(int));
    close(fd);
}
void receiveStrings()
{
    int fd = open("temp", O_RDONLY);
    read(fd, &message, sizeof(message));
    for(int j = 0; j < 5;)
	{
		printf("%s\n", message[j].text);
		j++;
	}
    printf("\n");
    close(fd);
}

int main(int argc, char* argv[])
{
    for(int i = 0; i < 50;)
	{
        receiveStrings();
        sendIndex(i);
		i+=5;
    }

}