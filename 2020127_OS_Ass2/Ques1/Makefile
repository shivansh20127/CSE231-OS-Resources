all:op1.o op2.o
	gcc -w -o out main.c
	./out

op1.o:op1.c
	gcc -w -o op1.o op1.c
	gcc -w -o op1 op1.c

op2.o:op2.c
	gcc -w -o op2.o op2.c
	gcc -w -o op2 op2.c

clean:
	rm -f *.o op1 op2 main*.s *.out