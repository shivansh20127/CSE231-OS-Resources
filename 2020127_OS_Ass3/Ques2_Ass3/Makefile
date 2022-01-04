all:
	mkfifo temp
	gcc -w fifosender.c -o fifosender
	gcc -w fiforeceiver.c -o fiforeceiver
	gcc -w random.c -o random
	gcc -w receiver.c -o receiver

clean:
	rm -f fifosender fiforeceiver random receiver temp