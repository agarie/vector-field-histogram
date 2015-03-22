OBJECTS=histogram_grid.o polar_histogram.o vfh.o
EXAMPLES=create_histogram_grid
CC=gcc
CFLAGS=-Isrc -g -Wall -O3 -std=c99 -D_XOPEN_SOURCE=500
LDLIBS=-lm

all: build examples
build: $(OBJECTS)
examples: $(EXAMPLES)

%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

vfh.c: vfh.h src/histogram_grid.h src/polar_histogram.h

histogram_grid.c: src/histogram_grid.h

polar_histogram.c: src/polar_histogram.h src/histogram_grid.h

create_histogram_grid: examples/create_histogram_grid.c histogram_grid.o
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $@

clean:
	rm $(OBJECTS) $(EXAMPLES)
