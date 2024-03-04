#ifndef MEMORY_CLASS
#define MEMORY_CLASS

#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
class Card;
class Memory;

struct Card {
		std::string value;
		bool already_found;
};
class Memory {
	protected:
		int nb_types;
		std::vector< Card > cards; // size= 2*nb_types
		int nb_turns;
		int nb_revealed_pairs;
	public:
		Memory(): nb_types(0), cards(), nb_turns(0), nb_revealed_pairs(0) {}
		Memory(std::istream &);
		friend std::ostream & operator<<(std::ostream &, const Memory &);
		void add_two_cards(const std::string & S);
		void operator+=(const std::string & S);
		template < class RNG > void random_initialize(RNG &); 
		void display() const;
		std::pair<std::string,std::string> one_try(int,int);
		bool is_revealed(int i) const { return cards[i].already_found;}
		bool is_game_over() const { return nb_revealed_pairs==nb_types;}
		int get_nb_turns() const { return nb_turns;}
		int get_nb_cards() const { return 2*nb_types;}
		bool one_player_turn(); // asks the player two card numbers, display the two values and tells if it is okay;
};

template < class RNG > void Memory::random_initialize(RNG & G) {
	std::shuffle(cards.begin(),cards.end(),G);
	nb_turns=0;
	nb_revealed_pairs=0;
	return;
}
#endif
