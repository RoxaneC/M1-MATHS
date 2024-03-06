#include "echelleetserpent.hpp"

using namespace std;

#include <algorithm>

// question 3
SnakesAndLadders::SnakesAndLadders(int n, int N): n_players(n), n_board(N), players(n), board(N){
    for(int i=0 ; i<N ; i++){
        board[i]=i;
    }
};

// question 4
SnakesAndLadders::SnakesAndLadders(istream &in): players(), board(){
    in >> n_players;
    in >> n_board;
    players.resize(n_players);

    int i;
    while(in >> i){
        board.push_back(i);
    }
};

// question 7
ostream & operator<<(ostream &out, const SnakesAndLadders &SL){
    out << SL.n_players << "\n";
    out << SL.n_board << "\n";

    for(int i : SL.board){
        out << i << " ";
    }

    return out;
};

// question 9
int SnakesAndLadders::roll_dice(mt19937 &G) const{
    uniform_int_distribution<int> U(1,6);
    int dice = U(G);
    return dice;
};

// question 10
bool SnakesAndLadders::one_step(mt19937 &G, int j){
    int dice = roll_dice(G);

    // cout << "Résultat du dé : " << dice << "\n";

    int new_pos = get_position(j) + dice;
    players[j].n_step++;

    // cout << "Le joueur passe de la position " << get_position(j);

    if(new_pos>=n_board-1){
        return true;
    } else {
        new_pos = board[new_pos];
        bool is_occupied = any_of(  players.begin(), players.end(),
                                    [new_pos](const Player &P){    return new_pos==P.position;} );
        
        players[j].position = (is_occupied) ? board[0] : new_pos;

        // cout << " à la position " << get_position(j) << "\n";
        return false;
    }
};

// question 12
int SnakesAndLadders::game(mt19937 &G){
    bool game_ended = false;
    int winner;

    while(!game_ended){
        for(int i=0 ; i<n_players ; i++){
            if(one_step(G,i) && !game_ended){
                winner = i;
                game_ended = true;
            }
        }
    }

    return winner;
};

// question 13
void SnakesAndLadders::reset(){
    for(int i=0 ; i<n_players ; i++){
        players[i].position = 0;
        players[i].n_step = 0;
    }
};