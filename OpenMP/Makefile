
HELLO_WORLD = helloworld
XCOMP = xcomp
XFIND = xfind

CC++ = g++
CC = cc

CPPFLAGS = -fopenmp -std=c++11
CFLAGS = -Xpreprocessor -fopenmp
LDFLAGS =  -lomp

OBJS = $(wildcard *.o)

$(HELLO_WORLD) : helloworld.o sha512.o
	$(CC++) $(CPPFLAGS) -o $(HELLO_WORLD) helloworld.o sha512.o

$(XCOMP) : xcomp.o
	$(CC++) $(LDFLAGS) -o $(XCOMP) -g xcomp.o

$(XFIND) : xfind.o chrono.h
	$(CC) $(LDFLAGS) -o $(XFIND) -g xfind.o 

helloworld.o:
	$(CC++) $(CPPFLAGS) -c helloworld.cpp

sha512.o: sha512.hpp
	$(CC++) $(CPPFLAGS) -c sha512.cpp

xfind.o : 
	$(CC) $(CFLAGS) -c xfind.c

clean:
	rm -rf $(HELLO_WORLD) $(XCOMP) $(XFIND) $(OBJS)