#include "echelleetserpent.hpp"

using namespace std;

#include <fstream>
#include <ctime>

int main(){
    // question 8
    SnakesAndLadders S;
    int n=1; int N=100;
    SnakesAndLadders S_trivial(n, N);

    cout << S_trivial << "\n\n";

    ifstream file_S("jeu.dat");
    SnakesAndLadders S1(file_S);

    cout << "La case 4 est-elle une echelle ? (1:oui ; 0:non) " << S1.is_ladder(3) << "\n"; // oui (1)

    // question 11
    double mean_dice = 0.;
    mt19937 G(time(NULL));
    for(int i=0 ; i<100 ; i++){
        mean_dice += S_trivial.roll_dice(G);
    }
    cout << "Moyenne enpirique du dé à 6 face (supposé équilibré) : " << mean_dice/100 << "\n\n";

    S_trivial.one_step(G,0);
    S_trivial.one_step(G,0);
    S_trivial.one_step(G,0);

    // question 14
    //

    return 0;
}