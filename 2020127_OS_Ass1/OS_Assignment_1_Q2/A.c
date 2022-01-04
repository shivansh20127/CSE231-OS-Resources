#include<stdio.h>
#include<stdlib.h>
extern B(void);
void a()
{
    printf("I am in A.. ready to going to B\n");
    long long int to_pass;
	printf("Enter the value to pass to B\n");
    scanf("%lld",&to_pass);
    b(to_pass);
}