

CC++ = clang++

# LDFLAGS = -lOpenCL

OBJS = $(wildcard *.o)

HELLO_WORLD = helloWorld

helloWorld : helloWorld.o
	$(CC++) $(LDFLAGS) -o helloWorld helloWorld.cpp

clean: 
	rm -rf $(HELLO_WORLD) $(OBJS)