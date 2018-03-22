
HELLO_WORLD = helloworld
XCOMP = xcomp
CC = clang++
CPPFLAGS = -Xpreprocessor -fopenmp -std=c++11
LDFLAGS =  -lomp
IFLAGS = -Iinclude
OBJS = helloworld.o sha512.o

$(HELLO_WORLD) : $(OBJS)
	$(CC) $(LDFLAGS) -o $(HELLO_WORLD) $(OBJS)

$(XCOMP) : xcomp.o
	$(CC) $(LDFLAGS) -o $(XCOMP) xcomp.o -g

helloomp.o:
	$(CC) $(CPPFLAGS) -c helloworld.cpp

sha512.o: sha512.hpp
	$(CC) $(CPPFLAGS) -c sha512.cpp

clean:
	rm -rf $(HELLO_WORLD) $(XCOMP) xcomp.o $(OBJS)