CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99

all: programa

programa: main.o tp1.o
	$(CC) $(CFLAGS) -o programa main.o tp1.o

main.o: main.c tp1.h
	$(CC) $(CFLAGS) -c main.c

tp1.o: tp1.c tp1.h
	$(CC) $(CFLAGS) -c tp1.c

clean:
	rm -f *.o programa
