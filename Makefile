CC=gcc
CFLAGS=
compile: 
	$(CC) -o roll src/roll.c

install:
	mv roll /usr/bin/roll
