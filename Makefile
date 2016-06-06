OBJECTS=histogram_grid.o polar_histogram.o vfh.o
EXAMPLES=create_histogram_grid
CC=gcc
CFLAGS=-Iinclude -Wall -O3 -std=c99
LDLIBS=-lm

all: build examples clean_objs
build: $(OBJECTS)
examples: $(EXAMPLES)

%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

vfh.c: include/vfh.h include/histogram_grid.h include/polar_histogram.h

histogram_grid.c: include/histogram_grid.h

polar_histogram.c: include/polar_histogram.h include/histogram_grid.h

create_histogram_grid: examples/create_histogram_grid.c histogram_grid.o
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $@

clean_objs:
	rm -f $(OBJECTS)

clean: clean_objs
	rm -f $(EXAMPLES)
