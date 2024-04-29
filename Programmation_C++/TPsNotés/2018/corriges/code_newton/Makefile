all: test_sin.exe sqrt.exe test_polynome.exe

CFLAGS = -std=c++11 -O2 -pedantic -Wall

test_sin.exe: test_sin.cpp newton.hpp 
	g++ $(CFLAGS) test_sin.cpp -o test_sin.exe
	
sqrt.exe: sqrt.cpp newton.hpp
	g++ $(CFLAGS) sqrt.cpp -o sqrt.exe
	
test_polynome.exe: test_polynome.cpp polynome.hpp newton.hpp
	g++ $(CFLAGS) test_polynome.cpp -o test_polynome.exe
	
clean:
	rm -rf *.o *.exe

