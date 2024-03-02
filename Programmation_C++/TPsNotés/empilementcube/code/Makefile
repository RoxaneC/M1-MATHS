CC= g++
CFLAGS= -std=c++11 -O2 -Wall -pedantic

all: test.exe alea.exe

empilementcube.o: empilementcube.hpp empilementcube.cpp
	$(CC) -c empilementcube.cpp $(CFLAGS) 
	
test.exe: empilementcube.o test.cpp 
	$(CC) empilementcube.o test.cpp $(CFLAGS)  -o test.exe

alea.exe: alea.cpp empilementcube.o
	$(CC) empilementcube.o alea.cpp $(CFLAGS) -o alea.exe 

clean:
	rm -f *.o *.exe
	
