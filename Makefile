#
# Makefile for simple PS executable
#

CC = gcc
CFLAGS = -g -Wall
OBJECTS = main.o parser.o options.o list.o

simplePS : $(OBJECTS)
	$(CC) $(CFLAGS) -o simplePS $(OBJECTS)

%.o : %.c
	$(CC) $(CFLAGS) -c $<
