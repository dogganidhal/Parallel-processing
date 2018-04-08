

OS = $(shell uname)
ifeq ($(OS), Darwin)
CXX = clang++
endif

LDFLAGS = -framework OpenCL
IFLAGS = -I../helpers/

OBJS = $(wildcard *.o)

HELLO_WORLD = ocl

$(HELLO_WORLD) : helloWorld.o
	$(CC) -o $(HELLO_WORLD) helloWorld.o $(LDFLAGS) $(IFLAGS)

helloWorld.o:
	$(CC) -c helloWorld.c $(IFLAGS)

clean: 
	rm -rf $(HELLO_WORLD) $(OBJS)