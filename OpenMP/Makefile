
HELLO_WORLD = omp
XCOMP = xcomp
XFIND = xfind

OS = $(shell uname)
ifeq ($(OS), Darwin)
CXX = clang++
endif

CPPFLAGS = -fopenmp -std=c++11
CFLAGS = -fopenmp

OBJS = $(wildcard *.o)

ifdef SILENT
.SILENT:
endif

$(HELLO_WORLD) : helloworld.o
	$(CXX) -o $(HELLO_WORLD) helloworld.o $(CPPFLAGS)

$(XCOMP) : xcomp.o
	$(CXX) $(LDFLAGS) -o $(XCOMP) -g xcomp.o

$(XFIND) : xfind.o chrono.h
	$(CC) $(LDFLAGS) -o $(XFIND) -g xfind.o 

helloworld.o:
	$(CXX) $(CPPFLAGS) -c helloworld.cpp

sha512.o: sha512.hpp
	$(CXX) $(CPPFLAGS) -c sha512.cpp

xfind.o : 
	$(CC) $(CFLAGS) -c xfind.c

clean:
	rm -rf $(HELLO_WORLD) $(XCOMP) $(XFIND) $(OBJS)
