all: test1.exe test2.exe approx.exe

COMPILO = g++
CPPFLAGS = -O2 -Wall -pedantic

approx.exe: approx.o interpolation.o
	$(COMPILO) approx.o interpolation.o -o approx.exe
	
approx.o: approx.cpp
	$(COMPILO) $(CPPFLAGS) approx.cpp -c

test1.exe: test1.o interpolation.o
	$(COMPILO) test1.o interpolation.o -o test1.exe

test1.o: test1.cpp interpolation.hpp
	$(COMPILO) $(CPPFLAGS) -c test1.cpp
	
test2.exe: test2.o interpolation.o
	$(COMPILO) test2.o interpolation.o -o test2.exe

test2.o: test2.cpp interpolation.hpp
	$(COMPILO) $(CPPFLAGS) -c test2.cpp

interpolation.o: interpolation.cpp interpolation.hpp
	$(COMPILO) $(CPPFLAGS) -c interpolation.cpp
	
clean:
	rm -f *.o *.exe

