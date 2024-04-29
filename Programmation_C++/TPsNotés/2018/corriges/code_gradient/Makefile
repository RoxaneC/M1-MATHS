all: quartic.exe test2d.exe

CFLAGS= -std=c++11 -O2 -Wall -pedantic

quartic.exe: gradient.hpp quartic.cpp
	g++ $(CFLAGS) quartic.cpp -o quartic.exe
	
test2d.exe: gradient.hpp vect.hpp test2d.cpp
	g++ $(CFLAGS) test2d.cpp -o test2d.exe
	
clean:
	rm -rf *.o *.exe

