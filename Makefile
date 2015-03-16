TARGET=vfh
OBJECTS=vfh.o
CC=gcc
CFLAGS=-c -g -Wall -O3
LDFLAGS=-lm
INCLUDES=-I.

# all: $(OBJECTS)
$(TARGET): $(OBJECTS)

%.o: %.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) $< -o $@

vfh.c: vfh.h

clean:
	rm $(OBJECTS)
