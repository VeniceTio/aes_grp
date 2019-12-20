all: main aes utils

prog: main.o aes.o utils.o
	gcc -Wall -o main main.o aes.o utils.o

main: main.c
	gcc -Wall -o main -c main.c
	
aes.o: aes.h aes.c
	gcc -Wall -c aes.c

utils.o: utils.h utils.c
	gcc -Wall -c utils.c

clean:
	rm *.o main
