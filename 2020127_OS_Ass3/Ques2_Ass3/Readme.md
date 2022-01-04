## Readme for Operating System (CSE 231) Assignment 3 Question 2

### [**Shivansh Choudhary - 2020127**]

## Description
	This question is based on how we can acheive Inter Process Communication for which it requires two processes to communicate and this can be done using FIFO , message queues and UNIX Domain Sockets.

## FIFO
	In this part we generate random strings and write them to a FIFO file or we can say in simpler words we can write to a FIFO file.  
	We make fifo file using mkfifo command and then we can write to it using write command. 
	We can read from it using read command.
	The reader process will read the data from the fifo file and print it on the screen and it will send the index of the last received string to the writer process.
	The writer process will read the index from the fifo file and will write the string at the index to the fifo file in the given struct format of 5 until all 5*10=50 strings are written.

	Steps to test the file: 
		1. Run make command in the terminal. You will see two files named as fiforeceiver and fifosender. 
		2. Then split the terminal into two windows and run the following commands in the two different windows:
				1. ./fiforeceiver     : This will run the receiver process.
				2. ./fifosender       : This will run the sender process.

		3. You will see the output of the two processes in the terminal.

## Message Queues
	First of all we created a struct data which contains information about our message or we can say it has strings which we will pass to the message queue.
	Both of these files created a queue which will be used to send and receive messages in a Inter Process Communication which will be acheived using the function msgget() , msgsnd() and msgrcv().
	There are 2 more structs msg_buffer and msg_rcv which will be used to send and receive messages and has uniques identifiers.
	The message queue will be created using the function msgget() and the message will be sent using the function msgsnd() and the message will be received using the function msgrcv().

	Steps to test the file:
		1. Run make command in the terminal. You will see two files named as random and receiver.
		2. Then split the terminal into two windows and run the following commands in the two different windows:
				1. ./receiver     : This will run the receiver process.
				2. ./random       : This will run the sender process.

		3. You will see the output of the two processes in the terminal.