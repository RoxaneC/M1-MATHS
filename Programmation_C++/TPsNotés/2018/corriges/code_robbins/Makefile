all: test1.exe solution.exe


test1.exe: robbinsmonro.hpp test1.cpp
	g++ -std=c++11 -O2 -Wall -pedantic test1.cpp -o test1.exe
	
explin.o: explin.hpp explin.cpp
	g++ -std=c++11 -O2 -Wall -pedantic explin.cpp -c
	
solution.exe: solution.cpp robbinsmonro.hpp explin.o
	g++ -std=c++11 -O2 -Wall -pedantic  explin.o solution.cpp -o solution.exe

clean:
	rm -rf *.exe *.o

