# Readme of Question 1

In the main, we call the fork system call and store the return type, i.e., we will have 0 for child and child process id for the parent process in the changeable. 

In the parent process, we perform two forks that will create SR and ST child processes. In these two child, we use execlp to replace the current working process with those directed files.

syntax of execlp command : 
* execlp(path, arg1, arg2, ..., NULL)

The first parameter is the path of the file to be executed. The remaining parameters are the arguments to be passed to the new process.But in this we will pass the pid of S1 child process which is to be given in the argument array of the execlp command to both `op1.c` and `op2.c`.

In the child process, we create a struct of sigaction. This struct will invoke our signal handler each time a signal is received with id=15 as we have defined this above and as this is the SIGTERM id. The signal handler is invoked by the kernel when the signal is received. It's one parameter is siginfo_t, a structure that contains information about the signal and has a sigval member, a union of int and void pointer in it. This union stores the pointer which been passed by the signal handler in op1 and op2. Then we can print the number received by casting it into uni64_t int and print it.

Inside the `op1.c` we use sigqueue to send the signal to the S1 child process i.e itself and with the SIGALARM signal we enqueue the pid of S1 which is received as an argument in the main. Then we will set the flags to SA_SIGINFO to get the information about the signal and the signal handler will be invoked. Then we set a timer using setitimer which will be invoked by the signal handler and that wil send alarms to the S1 child process repeatedly.

Inside the signal handler, we call the genrandom() function to generate a random number using the inline assembly and will return this number. Then using sigqueue, we queue this generated random number with the sigterm signal and transfer them both to the S1 child handler, which calls the signal handler and prints the random number as sigterm signal is also passed along with it.
We will use the inline assembly of C to generate an unsigned int 64-bit random number.


Inside the `op2.c` we use the main function of op1.c The sole difference is that here we use the CPU clock ticks using rdtsc. Then we can calculate the time taken by the process by dividing clock ticks with the CPU frequency and then queue it along with the sigterm signal in the S1 child process. Then we calculate the year,month,date,hour,minute,second using mathematical functions and queue it along with the sigterm signal in the S1 child process.
We will use inline assembly of C to generate a unsigned int 64 bit random number.
Then it is printing our desired output.



