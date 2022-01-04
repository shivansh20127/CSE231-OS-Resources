#This is the makefile to compile the Question 2 of the assignment
#the command rm -f is used to remove the old files in the directory
#the command make is used to compile the files
#the command make clean is used to remove the old files in the directory
#the command -no-pie is used to compile the files without the -pie flag
#the command nasm -f elf64 is used to compile the files with the nasm compiler

output_txt: q2.o A.o B.o C.o 
	gcc q2.o A.o B.o C.o -o output_txt -no-pie
	./output_txt
	rm -f output_txt

q2.o: q2.c
	gcc -c q2.c

A.o: A.c
	gcc -w -c A.c

B.o: B.asm
	nasm -f elf64 B.asm -o B.o

C.o: C.c
	gcc -c C.c

clean:
	rm -f *.o output_txt

