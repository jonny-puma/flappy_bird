#!/bin/make

LDFLAGS = -lncurses
CFLAGS = -O3 -Wall
DEPS = fp.h sprites.h highscore.h
CC = clang
OBJS = fp.o sprites.o highscore.o

flappy_bird : $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o : %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean
clean:
	rm -f *.o flappy_bird highscores.txt
