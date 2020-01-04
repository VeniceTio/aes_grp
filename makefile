CC=gcc

all: main main.o aes.o utils.o keyExpansion.o

main: main.o aes.o utils.o keyExpansion.o file.o
	gcc -o main -Wall main.o aes.o utils.o keyExpansion.o

main.o: main.c
	gcc -o main.o -Wall -c main.c

aes.o: aes.h aes.c
	gcc -o aes.o -Wall -c aes.c

utils.o: utils.h utils.c
	gcc -o utils.o -Wall -c utils.c

keyExpansion.o: keyExpansion.h keyExpansion.c
	gcc -o keyExpansion.o -Wall -c keyExpansion.c

file.o: file.h file.c
		gcc -o file.o -Wall -c file.c

clean:
	rm *.o main
