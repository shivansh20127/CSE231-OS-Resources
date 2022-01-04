## Readme for Operating System (CSE 231) Assignment 1 Question 2

### [**Shivansh Choudhary - 2020127**]

## Some basic definitions of terminology used in this assignment
	exit(var) : This function terminates the program with the exit status var (0 for success, 1 for failure).
	lea : This is a load effective address instruction. It loads the effective address of the variable into the accumulator or we can say into the destination register.
	rel : This is a relative address instruction. It loads the relative address of the variable into the accumulator or we can say into the destination register.
	mov : This is a move instruction. It moves the contents of the source register into the destination register.
	ret : This is a return instruction. It returns from the current function.
	call : This is a call instruction. It calls the function specified by the effective address.
	syscall : This is a system call instruction. It calls the system function specified by the effective address.
	global : This is a global declaration. It declares a variable as global.
	extern : This is an extern declaration. It declares a variable as extern.
	section .bss : Block starting symbol (abbreviated to .bss or bss) is the portion of an object file, executable, or assembly language code that contains statically allocated variables that are declared but have not been assigned a value yet. It is often referred to as the "bss section" or "bss segment". The bss section is the only section in an object file that is not initialized to zero.
	section .data : This is the data section. It contains the initialized variables and constants that are used by the program and are not modified by the program itself (i.e. the variables that are initialized by the program) and are used by the program to perform its operations (i.e. the variables that are modified by the program).

## Explanation of the code 
	We start the code from main function.
	Inside the main function we called another function A() which is defined in the code and declared in another file.
	In that function we declared a variable long long int to_pass (to support 64 bit system) and took the value of the variable from the user using scanf function.
	We then called another function B() which is defined in the code and declared in another file(.asm file) as it is written in assembly language.
	In that function we used section .bss to declare a variable. 
	In that function we used section .data to declare the global function.
	Then in that function declaration we first called the print function defined in the code in that function we used system calls to print the ACSII value the variable which was passed from function A.
	After returning from that print function we used lea command to load the address of C into r10 (which is a scratch register) and then we pushed that value into the stack.
	We can even use rdx,r9,r11,rbp and many more inplace of r10.
	Then when we return from the function the compiler finds the address of C at the top of the stack and the compiler goes to function C instead of returning back to A.
	It along way prints the message to show the current status i.e where the code is executing currently.
	Then in funciton C it prints a message that it has reached C and the code exits and Finally we used the exit function to terminate the program with status 0.

## Steps to run the code
	You can either run the code through the Makefile provided using make command or you can run the code by running the executable file for which the syntax is as follows:
	nasm -f elf64 B.asm -o B.o
	gcc q2.o A.o B.o C.o -o output_txt -no-pie
	./output_txt
	and you will se the output in the terminal.

## Resources used:
	https://flint.cs.yale.edu/cs421/papers/x86-asm/asm.html
	https://www.youtube.com/playlist?list=PLjCrdTxPv8nCz28U3BTtl5jOFq-RtREaR
	https://www.bipom.com/bashelp/assembly.htm