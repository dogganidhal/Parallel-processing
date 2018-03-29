

OS = $(shell uname)
ifeq ($(OS), Darwin)
CXX = clang++
endif

LIBS+= -lOpenCL

OBJS = $(wildcard *.o)

HELLO_WORLD = helloWorld

helloWorld : helloWorld.o
	$(CXX) -o helloWorld helloWorld.cpp -framework OpenCL

clean: 
	rm -rf $(HELLO_WORLD) $(OBJS)