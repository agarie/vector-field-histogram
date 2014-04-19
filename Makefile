P=vfh
OBJECTS= vfh.o
CPPFLAGS= -g -Wall -I. -O3 -gstabs
LDLIBS= -lm

$(P): $(OBJECTS)

example:

test:

clean:
	rm no-velocity vfh.o
