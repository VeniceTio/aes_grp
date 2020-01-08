CC=gcc

all: main main.o mainAlice.o aes.o utils.o keyExpansion.o file.o mainAlice Decode.o Encode.o Encode Decode

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

Encode.o: Encode.c
	gcc -o Encode.o -Wall -c Encode.c

Decode.o: Decode.c
	gcc -o Decode.o -Wall -c Decode.c

Encode: Encode.o aes.o utils.o keyExpansion.o file.o
	gcc -o Encode -Wall Encode.o aes.o utils.o keyExpansion.o file.o

Decode: Decode.o aes.o utils.o keyExpansion.o file.o
	gcc -o Decode -Wall mainAlice.o aes.o utils.o keyExpansion.o file.o
clean:
	rm *.o main
