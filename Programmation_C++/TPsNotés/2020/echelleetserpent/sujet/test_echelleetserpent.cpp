#include "echelleetserpent.hpp"

using namespace std;

#include <fstream>
#include <ctime>
#include <cmath>

int main(){
    // question 8
    SnakesAndLadders S;
    int n=1; int N=100;
    SnakesAndLadders S_trivial(n, N);

    cout << S_trivial << "\n\n";

    ifstream file_S("jeu.dat");
    SnakesAndLadders S1(file_S);

    cout << "La case 4 est-elle une échelle ? (1:oui ; 0:non) " << S1.is_ladder(3) << "\n"; // oui (1)

    // question 11
    double mean_dice = 0.;
    mt19937 G(time(NULL));
    for(int i=0 ; i<100 ; i++){
        mean_dice += S_trivial.roll_dice(G);
    }
    cout << "Moyenne empirique du dé à 6 face (supposé équilibré) : " << mean_dice/100 << "\n\n";

    S_trivial.one_step(G,0);
    S_trivial.one_step(G,0);
    S_trivial.one_step(G,0);

    // question 14
    int n_parties = 10000;
    int nbs_coups = 0;
    int nbs_coups_carre = 0;
    for(int i=0 ; i<n_parties ; i++){
        int winner = S1.game(G);
        nbs_coups += S1.get_n_step(winner);
        nbs_coups_carre += pow(S1.get_n_step(winner),2);
        S1.reset();
    }

    double moy = double(nbs_coups)/n_parties;
    double var =  double(nbs_coups_carre)/n_parties - pow(moy,2);
    cout << "Nombre moyen de coups pour finir une partie : " << moy << "\n";
    cout << "Écart-type du nombre de coups pour finir une partie : " << sqrt(var) << "\n";

    return 0;
}