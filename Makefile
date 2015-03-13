TARGET=vfh
OBJECTS= vfh.o
CC=gcc
CFLAGS= -c -g -Wall -pedantic -I. -O3 -std=c99
LDLIBS= -lm

all: static

static:
	$(CC) $(CFLAGS) vfh.c -o vfh.o
	ar rcs libvfh.a vfh.o

clean:
	rm vfh.o libvfh.a
