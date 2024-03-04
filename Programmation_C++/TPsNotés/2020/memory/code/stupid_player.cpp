#include <iostream>
#include <fstream>
#include <random>
#include "memory.hpp"

using namespace std;

int main() {
	ifstream set_of_cards("example2.dat");
	mt19937 G(time(NULL));
	Memory M(set_of_cards);
	
	const int N=1000;
	uniform_int_distribution<int> U(0,M.get_nb_cards()-1);
	
	long int moy_nb_turns=0;
	
	int a, b;
	for (int i = 0; i < N; i++)
	{
		M.random_initialize(G);	
		while( !M.is_game_over() )  {
			do {
				a=U(G);
				b=U(G);
			} while ((a==b) && !M.is_revealed(a) && !M.is_revealed(b));
			M.one_try(a,b);
		} 
		moy_nb_turns += M.get_nb_turns();
	}
	
	cout << "Average number of turns: "<< double(moy_nb_turns)/double(N) << "\n";
	return 0;
}

