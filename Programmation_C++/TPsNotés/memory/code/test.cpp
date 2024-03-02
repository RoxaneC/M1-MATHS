#include <iostream>
#include <fstream>
#include <random>
#include "memory.hpp"

using namespace std;

int main() {
	mt19937 G(time(NULL));

// 	Avec le constructeur vide et add_two_cards:

	Memory M0;
	M0.add_two_cards("chien");
	M0 += "chat";
	M0 += "oiseau";
	cout << "Initial configuration M0:\n" << M0 << "------\n";
	

// En lisant le fichier:

	ifstream set_of_cards("example1.dat");
	Memory M(set_of_cards);
	cout << "Initial configuration M:\n" << M << "------\n";
	
// Mélange:	
	
	M0.random_initialize(G);
	M.random_initialize(G);
	cout << "Shuffled configuration M0:\n" << M0 << "------\n";
	cout << "Shuffled configuration M:\n" << M << "------\n";

	return 0;
}
