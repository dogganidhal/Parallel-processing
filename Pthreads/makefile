
IFLAGS = -I../helpers/
CFLAGS = -Wall -Wextra
CPPFLAGS = -std=c++11 $(CFLAGS)

OBJ = $(wildcard *.o)
TARGETS = pthreads cppthreads

pthreads: pthreads.o
	$(CC) -o pthreads pthreads.o $(CFLAGS) $(IFLAGS)

pthreads.o:
	$(CC) -c pthreads.c $(IFLAGS) $(CFLAGS)

cppthreads: cppthreads.o
	$(CXX) -o cppthreads cppthreads.o $(CPPFLAGS) $(IFLAGS)

cppthreads.o:
	$(CXX) -c cppthreads.cpp $(IFLAGS) $(CPPFLAGS)



clean: 
	rm -rf *.o $(TARGETS)