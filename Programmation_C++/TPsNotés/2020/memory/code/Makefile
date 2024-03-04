all: partie.exe test.exe stupid_player.exe

memory.o: memory.hpp memory.cpp
	g++ -c memory.cpp -O2
	
partie.exe: partie.cpp memory.o memory.hpp
	g++ memory.o partie.cpp -o partie.exe -O2
	
test.exe: test.cpp memory.o memory.hpp
	g++ memory.o test.cpp -o test.exe -O2
	
stupid_player.exe: stupid_player.cpp memory.o memory.hpp
	g++ memory.o stupid_player.cpp -o stupid_player.exe -O2
