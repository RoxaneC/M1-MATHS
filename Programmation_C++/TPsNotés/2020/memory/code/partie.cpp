#include <iostream>
#include <fstream>
#include <random>
#include "memory.hpp"

using namespace std;

int main() {

	ifstream set_of_cards("example2.dat");
	std::mt19937 G(time(NULL));
	
	Memory M(set_of_cards);
	M.random_initialize(G);
	
	while( !M.is_game_over() ) M.one_player_turn();
	cout << "!!!!! You win after "<< M.get_nb_turns() << " turns !!!!!\n";	
	return 0;
}
