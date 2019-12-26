CC=gcc

all: main main.o aes.o utils.o keyExtention.o

main: main.o aes.o utils.o keyExtention.o
	gcc -o main -Wall main.o aes.o utils.o keyExtention.o 

main.o: main.c
	gcc -o main.o -Wall -g main.c
	
aes.o: aes.h aes.c
	gcc -o aes.o -Wall -g aes.c

utils.o: utils.h utils.c
	gcc -o utils.o -Wall -g utils.c

keyExtention.o: keyExtention.h keyExtention.c
	gcc -o keyExtention.o -Wall -g keyExtention.c

clean:
	rm *.o main
