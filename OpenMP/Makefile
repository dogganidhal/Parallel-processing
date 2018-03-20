
HELLO_WORLD = helloworld
ND_COMP = xcomp
CC = clang++
CPPFLAGS = -Xpreprocessor -fopenmp -std=c++11
LDFLAGS =  -lomp
IFLAGS = -Iinclude
OBJS = helloworld.o sha512.o

$(HELLO_WORLD) : $(OBJS)
	$(CC) $(LDFLAGS) -o $(HELLO_WORLD) $(OBJS)

$(ND_COMP) : xcomp.o
	$(CC) $(LDFLAGS) -o $(ND_COMP) xcomp.o -g

helloomp.o:
	$(CC) $(CPPFLAGS) -c helloworld.cpp

sha512.o: sha512.hpp
	$(CC) $(CPPFLAGS) -c sha512.cpp

clean:
	rm -rf $(HELLO_WORLD) $(ND_COMP) xcomp.o $(OBJS)