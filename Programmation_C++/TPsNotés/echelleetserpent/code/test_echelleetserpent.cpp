#include "echelleetserpent.hpp"

using namespace std;

int main(){
	
	// question 8
    SnakesAndLadders S;
    cout << S << endl;
    
    SnakesAndLadders S_trivial(1,100);
    cout << S_trivial << endl;
    
    ifstream file("jeu.dat");
    SnakesAndLadders S1(file);
    cout << S1 << endl;
    string s =  (S1.is_ladder(3))? "yes":"no";
    cout << "S1 échelle en 3 : " << s << endl;
    
    // question 11
    std::mt19937 G(time(NULL));
    double sum_die = 0.;
    for (int i=0;i<1000; ++i) 
		sum_die += S_trivial.roll_die(G);
	cout << "Moyenne dé 6 faces : " << sum_die/1000. << endl; 
	
	for (int i=0;i<3; ++i)
		S_trivial.one_step(0,G);
		
	cout << "Position :" << S_trivial.get_position(0) << endl;

	// question 14
    int n=10000;
    double sum = 0.;
    double sum_squared = 0.;
    for (int i=0;i<n; ++i){
		S1.reset();
		int winner = S1.game(G);
		int _n_step = S1.get_n_step(winner);
		sum += _n_step;
		sum_squared += _n_step*_n_step;
	}
	
	double mean = sum/(double)n;
	double variance = sum_squared/(double)n -mean*mean;
	cout << "Mean :" << mean << endl;
	cout << "Std dev : " <<  sqrt(variance) << endl;
    
    return 0;	
}
