

OS = $(shell uname)
ifeq ($(OS), Darwin)
CC = clang
endif

OBJS = $(wildcard *.o)

CSVGEN = csvgen

$(CSVGEN): $(CSVGEN).o
	$(CC) -o $(CSVGEN) $(CSVGEN).o

clean: 
	rm -rf $(CSVGEN) $(OBJS)