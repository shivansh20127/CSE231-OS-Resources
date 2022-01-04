#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>

#define __NR_kernel_2d_memcpy 448
int main()
{
    int n= 2, m = 4;
    float** src= (float**)malloc(n * sizeof(float*));
    for (int i= 0;i<n;i++)
    {
        src[i] = (float*)malloc(m*sizeof(float));
    }
    float** dest= (float**)malloc(n* sizeof(float*));
    for (int i = 0; i < n; i++)
    {
        dest[i] = (float*)malloc(m * sizeof(float));
    }
    for (int i= 0; i< n;i++)
    {
        for (int j= 0;j < m;j++)
        {
            src[i][j]=i+j+5;
        }
    }
    int tmp = syscall(__NR_kernel_2d_memcpy,src,dest,n,m);
    printf("\nFirst 2-d memory after calling syscall: \n");
    for (int i= 0;i<n;i++)
    {
        for (int j= 0;j<m;j++)
        {
            printf("%f ",src[i][j]);
        }
        printf("\n");
    }
    printf("\nSecond 2-d memory after calling syscall : \n");
    for (int i= 0;i<n;i++)
    {
        for (int j= 0;j<m;j++)
        {
            printf("%f ",dest[i][j]);
        }
        printf("\n");
    }
    return 0;
}
