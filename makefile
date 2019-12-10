all: main

aes.o: aes.h aes.c
	gcc -Wall -o aes.o -c aes.c

utils.o: utils.h utils.c	
	gcc -Wall -o utils.o -c utils.c

main: aes.o utils.o main.c
	gcc -Wall -o main aes.o utils.o main.c

clean:
	rm *.o main
