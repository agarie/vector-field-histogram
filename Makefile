TARGET=vfh
OBJECTS=histogram_grid.o polar_histogram.o vfh.o
EXAMPLES=create_histogram_grid
CC=gcc
CFLAGS=-I. -g -Wall -O3 -std=c99 -D_XOPEN_SOURCE=500
LDLIBS=-lm

all: build examples
build: $(OBJECTS)
examples: $(EXAMPLES)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

vfh.c: vfh.h histogram_grid.h polar_histogram.h

histogram_grid.c: histogram_grid.h

polar_histogram.c: polar_histogram.h histogram_grid.h

create_histogram_grid: examples/create_histogram_grid.c histogram_grid.o
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $@

clean:
	rm $(OBJECTS) $(EXAMPLES)
