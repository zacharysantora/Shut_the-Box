CC=g++
CXXFLAGS=--std=c++11 -g
TARGETS=box

all: $(TARGETS)
box: box.o 
box.o: box.cpp box.h

clean:
	rm -f *.o $(TARGETS)