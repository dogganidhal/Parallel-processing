CC = clang

LDFLAGS = -framework Foundation
IFLAGS = -I../helpers/ -I../helpers/

OBJS = $(wildcard *.o)

gcd :
	$(CC) -o gcd gcd.m $(LDFLAGS) $(IFLAGS)


clean: 
	rm -rf gcd $(OBJS)