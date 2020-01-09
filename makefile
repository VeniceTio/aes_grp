CC=gcc

all: main main.o mainAlice.o aes.o utils.o keyExpansion.o file.o mainAlice decode.o encode.o encode decode

main: main.o aes.o utils.o keyExpansion.o file.o
	gcc -o main -Wall main.o aes.o utils.o keyExpansion.o file.o

mainAlice: mainAlice.o aes.o utils.o keyExpansion.o file.o
	gcc -o mainAlice -Wall mainAlice.o aes.o utils.o keyExpansion.o file.o

main.o: main.c
	gcc -o main.o -Wall -c main.c

mainAlice.o: mainAlice.c
	gcc -o mainAlice.o -Wall -c mainAlice.c

aes.o: aes.h aes.c
	gcc -o aes.o -Wall -c aes.c

utils.o: utils.h utils.c
	gcc -o utils.o -Wall -c utils.c

keyExpansion.o: keyExpansion.h keyExpansion.c
	gcc -o keyExpansion.o -Wall -c keyExpansion.c

file.o: file.h file.c
	gcc -o file.o -Wall -c file.c

encode.o: encode.c
	gcc -o encode.o -Wall -c encode.c

decode.o: decode.c
	gcc -o decode.o -Wall -c decode.c

encode: encode.o aes.o utils.o keyExpansion.o file.o
	gcc -o encode -Wall encode.o aes.o utils.o keyExpansion.o file.o

decode: decode.o aes.o utils.o keyExpansion.o file.o
	gcc -o decode -Wall decode.o aes.o utils.o keyExpansion.o file.o
clean:
	rm *.o main
