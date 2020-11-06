#!/bin/make

ifeq ($(shell uname), Darwin)
	CC = clang
else
	CC = gcc
endif
LDFLAGS = -lncurses
ifdef debug
	CFLAGS = -g -Wall
else
	CFLAGS = -O3
endif
CFLAGS += -std=c99
DEPS = fp.h sprites.h highscore.h
OBJS = fp.o sprites.o highscore.o

flappy_bird : $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o : %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean
clean:
	rm -f *.o flappy_bird highscores.txt
uname:
	echo $(shell uname)	
