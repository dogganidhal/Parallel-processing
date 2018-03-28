
HELLO_WORLD = helloworld
XCOMP = xcomp
XFIND = xfind

CC++ = clang++
CC = clang

CPPFLAGS = -Xpreprocessor -fopenmp -std=c++11
CFLAGS = -Xpreprocessor -fopenmp
LDFLAGS =  -lomp

OBJS = $(wildcard *.o)

$(HELLO_WORLD) :
	$(CC++) $(LDFLAGS) -o $(HELLO_WORLD)

$(XCOMP) : xcomp.o
	$(CC++) $(LDFLAGS) -o $(XCOMP) -g xcomp.o

$(XFIND) : xfind.o chrono.h
	$(CC) $(LDFLAGS) -o $(XFIND) -g xfind.o 

helloomp.o:
	$(CC++) $(CPPFLAGS) -c helloworld.cpp

sha512.o: sha512.hpp
	$(CC++) $(CPPFLAGS) -c sha512.cpp

xfind.o : 
	$(CC) $(CFLAGS) -c xfind.c

clean:
	rm -rf $(HELLO_WORLD) $(XCOMP) $(XFIND) $(OBJS)