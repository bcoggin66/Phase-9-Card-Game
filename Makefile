CC = gcc
CFLAGS = -Wall -Wextra -std=c11

all: phase9

phase9: phase9.c phase9.h
	$(CC) $(CFLAGS) phase9.c -o phase9

clean:
	rm -f phase9 *.o
