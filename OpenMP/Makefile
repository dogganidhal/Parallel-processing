
PROG = omptest
CC = g++
CPPFLAGS = -Xpreprocessor -fopenmp -std=c++11
LDFLAGS =  -lomp
OBJS = helloomp.o sha512.o

$(PROG) : $(OBJS)
	$(CC) $(LDFLAGS) -o $(PROG) $(OBJS)

helloomp.o:
	$(CC) $(CPPFLAGS) -c helloomp.cpp

sha512.o: sha512.hpp
	$(CC) $(CPPFLAGS) -c sha512.cpp

clean:
	rm -rf $(PROG) $(OBJS)