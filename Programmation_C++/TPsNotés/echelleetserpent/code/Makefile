
all: test.exe

echelleetserpent.o: echelleetserpent.hpp echelleetserpent.cpp
	g++ -c echelleetserpent.cpp -O2 -std=c++11 -Wall -pedantic
	
test.exe: echelleetserpent.o test_echelleetserpent.cpp
	g++ echelleetserpent.o test_echelleetserpent.cpp -O2 -std=c++11 -o test.exe -Wall -pedantic

