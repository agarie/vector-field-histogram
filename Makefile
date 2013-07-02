P=vfh
OBJECTS= vfh.o
CPPFLAGS= -g -Wall -I. -O3 -gstabs
LDLIBS= -lm -lopencv_core -lopencv_highgui -lopencv_imgproc
CPP=g++

$(P): $(OBJECTS)

example:
	

clean:
	rm no-velocity vfh.o