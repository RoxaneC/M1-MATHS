#include "memory.hpp"

using namespace std;

std::ostream & operator<<(std::ostream & out, const Memory & M) {
	for (int i = 0; i < M.cards.size(); i++)
	{
		out << i << " " << M.cards[i].value << "  "; 
		if( M.cards[i].already_found ) {
			out << "revealed\n";
		} else {
			out << "hidden\n";
		}
	}
	out << M.nb_turns << "\n";
	out << M.nb_revealed_pairs << "\n";
	return out;
}

void Memory::add_two_cards(const string & S) {
	++nb_types;
	Card C;
	C.value = S;
	C.already_found= false;
	cards.push_back(C);
	cards.push_back(C);
}

void Memory::operator+=(const std::string & S) {
	add_two_cards(S);
	return;
}


void Memory::display() const{
	std::cout << "*** " << nb_turns+1 << "th turn ***\n" << "Configuration:\n";
	for (int i = 0; i < cards.size(); i++)
	{
		cout << "  "<<i << ": ";
		if ( cards[i].already_found== true) cout << cards[i].value << "\n";
		else cout << "?\n";
	}
	return;
}

Memory::Memory(istream & in): nb_types(0), cards(), nb_turns(0), nb_revealed_pairs(0) {
	in >> nb_types;
	cards.resize(2*nb_types);
	for (int i = 0; i < nb_types; i++)
	{
		in >> cards[2*i].value;
		cards[2*i].already_found;
		cards[2*i+1] = cards[2*i];
	}
	return;
}

pair<string,string> Memory::one_try(int i,int j) {
	nb_turns++;
	if ( cards[i].value == cards[j].value)
	{
		cards[i].already_found = true;
		cards[j].already_found = true;
		nb_revealed_pairs += 1;
	}
	return make_pair(cards[i].value,cards[j].value);
}

bool Memory::one_player_turn() {
	display();
	cout << "Enter two card numbers to reveal the two cards:\n" ;
	int i0,j0;
	cin >> i0 >> j0;
	while (  (i0 >= 2*nb_types) || (j0 >= 2*nb_types) || (i0==j0) ||cards[i0].already_found || cards[j0].already_found) {
		if( (i0==j0) ) std::cout << "--- Invalid guess: twice the same card ! ---\n";
		else if ( (i0 >= 2*nb_types) || (j0 >= 2*nb_types) ) std::cout << "--- Invalid guess: not valid cards ! ---\n";
		else std::cout << "--- Invalid guess: cards already revealed ! ---\n";
		std::cout << "--- Enter again two card numbers: ---\n";
		cin >> i0 >> j0;	
	}
	pair<string,string> result= one_try(i0,j0);
	bool match;
	if (result.first == result.second )
	{
		cout << "--- Correct guess ! ---\n";
		cout << i0 << " and " <<j0 << ": " << cards[i0].value << "\n";
		match=true;
	} else {
		cout << "--- Not identical ! Here are the values of the two cards: ---\n";
		cout << "      " << i0 << ": " << cards[i0].value << "\n";
		cout << "      " << j0 << ": " << cards[j0].value << "\n";
		match=false;
	}
	cout << "--- Press Enter to continue ---";
	cin.ignore();
	cin.ignore();
	return match;
}





