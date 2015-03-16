TARGET=vfh
OBJECTS=histogram_grid.o polar_histogram.o vfh.o
CC=gcc
CFLAGS=-I. -g -Wall -O3 -std=c99 -D_XOPEN_SOURCE=500
LDFLAGS=-I.
LDLIBS=-lm

all: $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

vfh.c: vfh.h histogram_grid.h polar_histogram.h

histogram_grid.c: histogram_grid.h

polar_histogram.c: polar_histogram.h histogram_grid.h

clean:
	rm $(OBJECTS)
