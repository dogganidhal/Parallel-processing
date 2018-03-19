
HELLO_WORLD = helloworld
ND_COMP = ndcomp
CC = clang++
CPPFLAGS = -Xpreprocessor -fopenmp -std=c++11
LDFLAGS =  -L"$(shell pwd)/dependencies/" -lomp
IFLAGS = -Iinclude
OBJS = helloomp.o sha512.o

$(HELLO_WORLD) : $(OBJS)
	$(CC) $(LDFLAGS) -o $(HELLO_WORLD) $(OBJS)

$(ND_COMP) : ndcomp.o
	$(CC) $(LDFLAGS) -o $(ND_COMP) ndcomp.o

helloomp.o:
	$(CC) $(CPPFLAGS) -c helloomp.cpp

sha512.o: sha512.hpp
	$(CC) $(CPPFLAGS) -c sha512.cpp

clean:
	rm -rf $(HELLO_WORLD) $(ND_COMP) ndcomp.o $(OBJS)