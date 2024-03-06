#ifndef MY_EeS
#define MY_EeS

#include <vector>
#include <iostream>
#include <random>

struct Player{
    int position;
    int n_step;
    Player(): position(0), n_step(0){};
};

class SnakesAndLadders{
    private:
        int n_players;
        int n_board;
        std::vector<Player> players;
        std::vector<int> board;

    public:
        // question 2
        SnakesAndLadders(): n_players(0), n_board(0), players(), board(){};

        // question 3
        SnakesAndLadders(int n, int N);

        // question 4
        SnakesAndLadders(std::istream &in);

        // question 5
        int get_position(int j) const { return players[j].position; };
        int get_n_step(int j) const {   return players[j].n_step; };

        // question 6
        bool is_ladder(int j) const {   return board[j]>j; };
        bool is_snake(int j) const {    return board[j]<j; };

        // question 7
        friend std::ostream & operator<<(std::ostream &out, const SnakesAndLadders &SL);

        // question 9
        int roll_dice(std::mt19937 &G);

        // question 10
        bool one_step(std::mt19937 &G, int j);
};

#endif