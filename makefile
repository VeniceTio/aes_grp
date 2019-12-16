all: main

main: main.c aes.o utils.o
    gcc -o main main.c aes.o utils.o

aes.o: aes.h aes.c
    gcc -o aes aes.c

utils.o: utils.h utils.c
    gcc -o utils utils.c

clean:
    rm o.*