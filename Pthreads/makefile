
IFLAGS = -I../helpers/
CPPFLAGS = -std=c++11 -Wall -Wextra

OBJ = main.o

main: main.o
	$(CXX) -o main main.o $(CPPFLAGS) $(IFLAGS)

main.o:
	$(CXX) -c main.cpp $(IFLAGS) $(CPPFLAGS)

clean: 
	rm -rf *.o main


#ALL IS OK