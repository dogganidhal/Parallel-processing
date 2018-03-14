

main: helloomp.o sha512.o
	clang++ -Xpreprocessor -fopenmp -lomp helloomp.o -o helloomp

helloomp.o: sha512.hpp
	clang++ helloomp.cpp sha512.hpp

sha512.o:
	clang++ sha512.cpp sha512.hpp

clean: 
	rm -rf helloomp