

CC = clang

OBJS = $(wildcard *.o)

HELLO_WORLD = helloWorld

helloWorld : helloWorld.o
	$(CC) -o helloWorld helloWorld.c

clean: 
	rm -rf $(HELLO_WORLD) $(OBJS)