TARGET=vfh
OBJECTS= vfh.o
CC=gcc
CFLAGS= -c -g -Wall -I. -O3
LDLIBS= -lm

all: $(TARGET)

$(TARGET): $(OBJECTS)

example:

test:

clean:
	rm no-velocity vfh.o
