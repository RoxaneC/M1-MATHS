all: test1.exe test_commerce.exe

test1.exe: recuit.hpp test1.cpp
	g++ -std=c++11 -O2 -Wall -pedantic test1.cpp -o test1.exe
	
voyageur.o:	voyageur.cpp voyageur.hpp
	g++ -std=c++11 -O2  -Wall -pedantic -c voyageur.cpp
	
test_commerce.exe: voyageur.o voyageur.hpp test_commerce.cpp recuit.hpp
	g++ -std=c++11 -O2  -Wall -pedantic voyageur.o test_commerce.cpp -o test_commerce.exe
	
clean:
	rm -rf *.exe *.o
