#include "voyageur.hpp"
#include "recuit.hpp"

#include <cmath>
#include <iostream>

using namespace std;

int main(){
    // question 8
    DistanceTotale DT(50);
    vector<int> traj(50);
    for(int i=0 ; i<50 ; i++){
        traj[i] = i;
        for(int j=0 ; j<50 ; j++){
            DT.distance(i,j) = cos(4*i + 3*j)*cos(4*i + 3*j);
        }
    }

    // question 9 ?
    // la fonciton intervertie au hasard deux élément dans le vecteur

    // question 10
    auto T = [](long unsigned n){   return 10*pow(0.95, n); };
    mt19937 Gen(time(nullptr));
    cout << "Longueur trajectoire initiale : " << DT(traj);
    cout << "Q10)\tLongueur du meilleur chemin : " << DT(recuit_simule(DT, traj, T, Y_transposition<mt19937>, Gen, 100000)) << "\n";

    return 0;
}