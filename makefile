all: main

main: main.c aes.o utils.o
	gcc -Wall -o main main.c aes.o utils.o

aes.o: aes.h aes.c
	gcc -Wall -c aes.c

utils.o: utils.h utils.c
	gcc -Wall -c utils.c

clean:
	rm *.o main
