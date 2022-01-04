#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<errno.h>
#include<fcntl.h>

char str[50][10];

struct mesg {
    int return_index;
    char text[10];
    int index;
} message[5];

void receiveIndex()
{
    int fd;
    fd = open("temp", O_RDONLY);
    int x;
    read(fd, &x, sizeof(int));
    printf("\nIndex Received: %d\n\n", x); 
    close(fd);
}

void generateStrings()
{
    for(int i = 0; i < 50;)
	{
        for(int j = 0; j < 9;)
		{
            char c = 'a' + rand() % 25;
            str[i][j] = c;
			j++;
        }
        str[i][10] = '\0';
		i++;
    }
}
void sendMessage(int i)
{
    int fd = open("temp", O_WRONLY);
    for(int j = 0; j < 5;)
	{
        message[j].index = 2*j+1;
        message[j].index = i;
        strcpy(message[j].text, str[i + j]);
        message[j].return_index = i + 4;
		j++;
    }
    write(fd, &message, sizeof(message));
    close(fd);
}

int main(int argc, char* argv[])
{
    generateStrings();
    for(int i = 0; i < 50;)
	{
        sendMessage(i);
        receiveIndex();
		i+=5;
    }
    return 0;
}