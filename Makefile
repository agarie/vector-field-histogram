TARGET=vfh
OBJECTS= vfh.o
CC=gcc
CFLAGS= -c -g -Wall -I. -O3 -std=c99
LDLIBS= -lm

all: static

static:
	$(CC) $(CFLAGS) $(LDLIBS) vfh.c -o vfh.o
	ar rcs libvfh.a vfh.o

clean:
	rm vfh.o libvfh.a
