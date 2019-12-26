all: main aes utils keyExtention

main: main.o aes.o utils.o keyExtention.o
	gcc -Wall main.o aes.o utils.o keyExtention.o

main.o: main.c
	gcc -Wall -c main.c
	
aes.o: aes.h aes.c
	gcc -Wall -c aes.c

utils.o: utils.h utils.c
	gcc -Wall -c utils.c

keyExtention.o: keyExtention.h keyExtention.c
	gcc -Wall -c keyExtention.c

clean:
	rm *.o main
