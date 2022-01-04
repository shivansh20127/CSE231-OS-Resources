#there is a sepeate command for each file type
#you can make .o or .S of which ever file you want whether part A or part B
#you can clean up the .o and executable files by running make clean
#you can run the executable by running make 
#you can make assembly by running make Ass-Q1A or make Ass-Q1B
#you can make object file by running make q1A.o or make q1B.o
#you can run individual files by running make q1A or make q1B

all:q1A.o q1B.o
	gcc -w q1A.o -o exe1 
	./exe1
	gcc -lpthread -w q1B.o -o exe2
	./exe2

q1A.o:q1.c
	gcc -w -c q1.c -o q1A.o

q1B.o:q1B.c
	gcc -pthread -w -c q1B.c -o q1B.o

Ass-Q1A:q1.c
	gcc -S -w q1.c

Ass-Q1B:q1B.c 
	gcc -lpthread -S -w q1B.c

q1A:q1.c
	gcc -w q1.c
	./a.out 

q1B:q1B.c
	gcc -lpthread -w q1B.c
	./a.out 

clean:
	rm -f *.o exe1 exe2 *.s *.out