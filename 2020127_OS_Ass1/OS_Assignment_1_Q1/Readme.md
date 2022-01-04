## Readme for Operating System (CSE 231) Assignment 1 Question 1

### [**Shivansh Choudhary - 2020127**]

## Some basic definitions of terminology used in this assignment
	What is fork() : In an operating system, a fork is a Unix or Linux system call to create a new process from an existing running process.
	lseek() : The lseek() function repositions the offset of the file descriptor fd to the argument offset bytes.
	open() : The open() function opens the file whose pathname is specified by filename and associates a file descriptor with it.
	waitpid() : The waitpid() function waits for a child process to die.
	malloc() : The malloc() function allocates memory dynamically during runtime andd returns a pointer to the allocated memory.
	strtok() : The strtok() function is a string tokenizer used to parse a string.
	read() : The read() function reads data from a file descriptor.
	thread() : A thread is a single sequential flow of execution of tasks of a process so it is also known as thread of execution or thread of control.
	struct : A structure is a collection of data types that are used to group data together to form a single compound data type or aggregate data type in C.
	pthread_create() : The pthread_create() function creates a thread in the calling process.
	pthread_join() : The pthread_join() function waits for the thread specified by thread to terminate.
	memset : The memset() function sets the first n bytes of the memory area pointed to by s to the specified value c.
	EXIT_FAILURE : The EXIT_FAILURE macro is defined in <stdlib.h> and is the value that shall be returned by the exit() function to indicate failure.

## Explanation of the code of Ques 1 Part A :
	Since this is a C file we can use the C preprocessor to include the header file.
	The header file contains the function prototypes of the functions we are going to use.
	Then we entered in main and use the fork() function to create a child process.
	To use fork() we need to include the header file <unistd.h>.
	The child process will execute functions and the parent process will execute same set of functions again.
	Before entering the child and parent process we checked whether the fork() function was successful or not.
	If the fork() function was successful then the child process will execute the code inside the if block and parent process will exectute the code inside the else block.
	Else the code prints a message saying that the fork() function was unsuccessful and code will exit.
	Before entering the child process we first loaded the files using the open() function.
	Then we used the lseek() function to move the file pointer to the end of the file and calculated the size of the file.
	Then we calculated commas in the file using the open() function and then traversing the cheking the current token is equal to the token we are looking for i.e comma and if it is then we increment the count.
	Then we again opened the file and load the contents of .csv file into a buffer array using the open() and load() function.
	Then we calculated number of students of each section and loaded the answer into a pair which was then used to assign the size of arrays we are using to print the scores.
	Then we come to main part i.e solving in different process.
	In child process we passed 'A' to denote that we have to calculate the average of each assignment of students of section A.
	In the parent process we passed 'B' to denote that we have to calculate the average of each assignment of students of section B.

	Inside each of these process we traversed through the loaded array and created a array or precisely struct of arrays to store the sum and average of each of the assignment.

	We used waitpid() function to wait for the child process to finish.
	And after the child process is finished we used the condition in else to run our parent process.
	And in each of our child and parent process we called cal_average() function to print the scores.

## Explanation of the code of Ques 1 Part B: 
	Since this is a C file we can use the C preprocessor to include the header file.
	The header file contains the function prototypes of the functions we are going to use.
	Then we entered in main and used two threads to run the two functionalities we want to acheive from the code.
	When we created two threads, we checked whether the creation of the thread was successful or not.
	If the creation of the thread was successful then the thread will execute the code inside the if block.
	Else we print the error message and code get exit with exit error status.
	The rest functionality of the reading the file and loading the data of .csv into a array is same as the code of Ques 1 Part A except we can't pass multiple arguments to the thread function.
	Hence for that purpose we passed a struct of type sec_data to the thread function denoting the section and assignment array which will store the scores of assignment of each section.
	The thread function will calculate the sum of each assignment of students of the respective section and store the sum in the struct of type sec_data.
	Then at last we printed the average of each assignment of students of the combined section.


## Reference used in Doing Ques 1:
	https://fresh2refresh.com/c-programming/c-file-handling/fseek-seek_set-seek_cur-seek_end-functions-c/
	https://www.delftstack.com/howto/c/pthread_join-return-value-in-c/
	https://www.kernel.org/doc/man-pages/ 
	https://www.javatpoint.com/file-handling-in-c
	https://en.wikipedia.org/wiki/Fork_(system_call) 
