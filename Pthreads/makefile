CC = cc -g -Wall -Wextra -Werror #-lpthread

OBJ = main.o

%.o: %.c
	$(CC) -c -o $@ $<

main: $(OBJ)
	gcc -o $@ $^

clean: 
	rm -rf *.o main