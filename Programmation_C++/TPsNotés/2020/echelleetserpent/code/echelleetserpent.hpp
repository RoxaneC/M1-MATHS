#ifndef SNAKESANDLADDERS
#define SNAKESANDLADDERS

#include <vector>
#include <iostream>
#include <fstream>
#include <set>
#include <algorithm>
#include <random>
#include <numeric>

struct Player{
	int position;
	int n_step;
	Player():position(0), n_step(0){};
};

class SnakesAndLadders{
private:
	int n_players;
	int n_board;
	std::vector<Player> players; 
	std::vector<int> board; 

public:
    // Constructeurs
    SnakesAndLadders(): n_players(0), n_board(0), players(), board(){}; // question 2
    SnakesAndLadders(int, int);
    SnakesAndLadders(std::istream&); 
    SnakesAndLadders(int, int , int , int , std::mt19937&);
    
    // Accesseurs
    int get_position(int j) const {return players[j].position;} //question 5
    int get_n_step(int j) const {return players[j].n_step;} 
    bool is_ladder(int j) const {return (board[j]>j)? true : false;} //question 6
    bool is_snake(int j) const {return (board[j]<j)? true : false;} 
    
    // Entrées-sorties:
	friend std::ostream& operator<<( std::ostream&, const SnakesAndLadders&); 
	
	// Jouer
    int roll_die(std::mt19937&) const;
    bool one_step(int, std::mt19937&);
    int game(std::mt19937&);
    
    // Recommencer une partie
    void reset();
};


#endif
