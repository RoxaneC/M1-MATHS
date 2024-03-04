#include "sandpile.hpp"

#include <vector>
#include <list>
#include <utility>
#include <algorithm>
#include <random>
#include <string>

using upair=std::pair<unsigned, unsigned>; //raccourci pour les paires d'entiers
using namespace std;

// question 2
Sandpile::Sandpile(unsigned m0, unsigned n0, unsigned k) :  m(m0), n(n0), terrain(n0*m0, k), nb_ebouls(n0*m0, 0), next_ebouls(){
    for(unsigned j=0 ; j<n ; j++){
        for(unsigned i=0 ; i<m ; i++){
            upair p(i,j);
            if(k>=4){
                next_ebouls.push_back(p);
            }
        }
    }
};

// question 4
// ajout question 18
ostream & operator<<(ostream &out, const Sandpile &s){
    string chars = ".oO0";
    for(int j=0 ; j<s.n ; j++){
        for(int i=0 ; i<s.m ; i++){
            if (s(i,j) <4){
                out << chars[s(i,j)];
            } else {
                out << s(i,j);
            }
        }
        out << "\n";
    }
    return out;
};

// question 7
list<upair> Sandpile::voisins(upair p) const {
    unsigned i = p.first;
    unsigned j = p.second;

    list<upair> list_voisins;

    if (i==0){
        if(j==0){
            list_voisins.push_back(upair(i, j+1));
            list_voisins.push_back(upair(i+1, j));
        } else if (j==n-1){
            list_voisins.push_back(upair(i+1, j));
            list_voisins.push_back(upair(i, j-1));
        } else {
            list_voisins.push_back(upair(i+1, j));
            list_voisins.push_back(upair(i, j-1));
            list_voisins.push_back(upair(i, j+1));
        }
    } else if (i==m-1) {
        if(j==0){
            list_voisins.push_back(upair(i, j+1));
            list_voisins.push_back(upair(i-1, j));
        } else if (j==n-1){
            list_voisins.push_back(upair(i-1, j));
            list_voisins.push_back(upair(i, j-1));
        } else {
            list_voisins.push_back(upair(i-1, j));
            list_voisins.push_back(upair(i, j-1));
            list_voisins.push_back(upair(i, j+1));
        }
    } else {
        if(j==0){
            list_voisins.push_back(upair(i, j+1));
            list_voisins.push_back(upair(i+1, j));
            list_voisins.push_back(upair(i-1, j));
        } else if (j==n-1){
            list_voisins.push_back(upair(i+1, j));
            list_voisins.push_back(upair(i-1, j));
            list_voisins.push_back(upair(i, j-1));
        } else {
            list_voisins.push_back(upair(i+1, j));
            list_voisins.push_back(upair(i-1, j));
            list_voisins.push_back(upair(i, j-1));
            list_voisins.push_back(upair(i, j+1));
        }
    }
    return list_voisins;
};

// question 9
void Sandpile::incr_and_test(upair &p){
    unsigned new_hauteur = h(p)+1;
    h(p, new_hauteur);
    if (new_hauteur >= 4)   next_ebouls.push_back(p);
};

// question 10
void Sandpile::eboul(upair &p){
    unsigned hauteur = h(p);

    if (hauteur >= 4){
        nb_ebouls[p.first + p.second*m]++;
        h(p, hauteur-4);

        for(upair pp : voisins(p)){
            incr_and_test(pp);
        }
    }
};

// question 11
int Sandpile::stabil(){
    int compteur = 0;

    while (!next_ebouls.empty()){
        upair p = next_ebouls.front();
        next_ebouls.pop_front();

        eboul(p);
        compteur++;
    }

    return compteur;
};

// question 12
int Sandpile::nb_total_ebouls() const {
    int compteur = 0;

    for(unsigned i : nb_ebouls){
        compteur += i;
    }

    return compteur;
};

// question 15
int Sandpile::add_random_grain(mt19937 &G, int k){
    //
    uniform_int_distribution<> Ui(0,m-1);
    uniform_int_distribution<> Uj(0,n-1);
    for(int l=0 ; l<k ; l++){
        //
        unsigned i = Ui(G);
        unsigned j = Uj(G);

        upair p(i,j);

        h(p, h(p)+1);
    }

    int nb = stabil();
    return nb;
};

// question 17
Sandpile operator+(const Sandpile &S1, const Sandpile &S2){
    //
    Sandpile new_S(S1.m, S1.n, 0);
    //
    for(unsigned j=0 ; j<new_S.n ; j++){
        for(unsigned i=0 ; i<new_S.m ; i++){
            upair p(i,j);
            new_S.h(p, S1.h(p)+S2.h(p));

            if(new_S.h(p)>=4){
                new_S.next_ebouls.push_back(p);
            }
        }
    }

    new_S.stabil();
    return new_S;
};