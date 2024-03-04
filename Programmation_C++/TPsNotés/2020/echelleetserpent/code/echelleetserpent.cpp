#include "echelleetserpent.hpp"

using namespace std;

// question 3
SnakesAndLadders::SnakesAndLadders(int n, int N): n_players(n), n_board(N), players(n), board(N){
	for (int i=0;i<N; ++i)
		board[i] = i;
}

// question 4
SnakesAndLadders::SnakesAndLadders(istream& in): board(){
	in >> n_players;
	Player player;
	players = vector<Player>(n_players, player);
	
	in >> n_board; 
	board.resize(n_board);
	
	for(int i=0; i<n_board; ++i)
		in >> board[i];	
}

// question 7
ostream& operator<<( ostream& out, const SnakesAndLadders& S) {
	
	out << S.n_players << "\n";
	out << S.n_board << "\n";
	
	for(int i=0;i<S.n_board;++i)
		out << S.board[i] << " ";
	
	return out;
}

// question 9
int SnakesAndLadders::roll_die(std::mt19937& gen) const{
    std::uniform_int_distribution<> U(1,6);
    return U(gen);
}

// question 10
bool SnakesAndLadders::one_step(int j, std::mt19937& gen){
	int step = roll_die(gen);
	
	//cout << "Die value : " << step << endl;
	
	int pos = min(players[j].position+step, n_board-1);
	pos = board[pos];
	players[j].n_step++;
	
	if(pos==n_board-1){
		players[j].position = pos;
		return true;
	}
	else{
		bool found_in_players = any_of(players.begin(), players.end(), [pos](Player p){return p.position == pos;});
		players[j].position = (found_in_players)? 0 : pos;
		return false;
	}
}

// question 12
int SnakesAndLadders::game(std::mt19937& gen){
	bool won = false;
	int winner;
	
	while(won!=true){
		for (int j=0; j<players.size(); ++j){
			if(one_step(j,gen) && won!=true){
				won = true;
				winner = j;
			}
		}
	}
	
	return winner;
}

// question 13
void SnakesAndLadders::reset(){
	for (int i=0; i<n_players; ++i){
		players[i].position = 0;
		players[i].n_step = 0;
	}
}
