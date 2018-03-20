CC = cc -g -Wall -Wextra -lpthread

OBJ = main.o

%.o: %.c
	$(CC) -c -o $@ $<

main: $(OBJ)
	gcc -o $@ $^

clean: 
	rm -rf *.o main


#ALL IS OK