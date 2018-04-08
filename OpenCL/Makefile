

OS = $(shell uname)
ifeq ($(OS), Darwin)
CXX = clang++
endif

LDFLAGS = -framework OpenCL
IFLAGS = -I../helpers/

OBJS = $(wildcard *.o)

OCL = ocl

$(OCL) : helloWorld.o
	$(CC) -o $(OCL) helloWorld.o $(LDFLAGS) $(IFLAGS)

helloWorld.o:
	$(CC) -c helloWorld.c $(IFLAGS)

clean: 
	rm -rf $(OCL) $(OBJS)