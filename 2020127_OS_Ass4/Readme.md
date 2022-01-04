## Readme for Operating System (CSE 231) Assignment 4

### [**Shivansh Choudhary - 2020127**]

## Introduction & Implementation
	In this assignment we are going to make read and write operations. To acheive this task we are going to declare two system calls in system cal table and then we are going to implement them in the code. To acheive the functionality of read and write we are going to first fork the process and then we are going to test the read and write system calls. The definition of both the system calls are declared in sys.c file. As demanded in the ques we will implement a circular queue and perform enqueue and dequeue operations on that queue. In write system call we will use enqueue operation and in read system call we will use dequeue operation. We will copy the data from the queue to the buffer and then we will copy the data from the buffer to the queue. The code for both the system calls is given in sys.c file. Only 1 operation will happen in a given time frame and the other operation will wait till the current operation is completed. For this we are using semaphores.

## Steps to test the system calls
	Open terminal 
	Go to the directory where the code is present
	Type the following command to compile the code

### gcc -lpthread 2020127test.c
### ./a.out