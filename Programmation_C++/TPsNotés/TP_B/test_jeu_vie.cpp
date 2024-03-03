#include "jeu_vie.hpp"

#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <random>

using namespace std;

// question 2
jeu_vie::jeu_vie(int _H, int _L): H(_H), L(_L), config(H){

    for(int i=0 ; i<H ; i++){
        vector<bool> v(L);
        for(int j=0 ; j<L ; j++){
            v[j] = false;
        }
        config[i] = v;
    }
};

// question 4 (bourrin)
int jeu_vie::voisins(int i, int j) const {
    int compteur = 0;

    if(i==0){
        compteur += config[i+1][j];
        if(j==0){
            compteur += config[i][j+1];
            compteur += config[i+1][j+1];
        } else if (j==L-1){
            //
            compteur += config[i][j-1];
            compteur += config[i+1][j-1];
        } else {
            compteur += config[i][j+1];
            compteur += config[i][j-1];
            compteur += config[i+1][j+1];
            compteur += config[i+1][j-1];
        }
    } else if(i==H-1){
        compteur += config[i-1][j];
        if(j==0){
            compteur += config[i][j+1];
            compteur += config[i-1][j+1];
        } else if (j==L-1){
            //
            compteur += config[i][j-1];
            compteur += config[i-1][j-1];
        } else {
            compteur += config[i][j+1];
            compteur += config[i][j-1];
            compteur += config[i-1][j+1];
            compteur += config[i-1][j-1];
        }
    } else {
        compteur += config[i+1][j];
        compteur += config[i-1][j];
        if(j==0){
            compteur += config[i][j+1];
            compteur += config[i+1][j+1];
            compteur += config[i-1][j+1];
        } else if (j==L-1){
            compteur += config[i][j-1];
            compteur += config[i-1][j-1];
            compteur += config[i+1][j-1];
        } else {
            compteur += config[i][j+1];
            compteur += config[i][j-1];
            compteur += config[i+1][j+1];
            compteur += config[i+1][j-1];
            compteur += config[i-1][j+1];
            compteur += config[i-1][j-1];
        }
    }
    return compteur;
};

// question 6
void jeu_vie::iteration(){
    vector<vector<bool>> new_config = config;

    for(int i=0 ; i<H ; i++){
        for(int j=0 ; j<L ; j++){
            int nb_voisins = voisins(i,j);

            if (nb_voisins==3)
                new_config[i][j] = true;

            if (nb_voisins<=1 || nb_voisins>=4)
                new_config[i][j] = false;
        }
    }

    config = new_config;
};

// question 7
void jeu_vie::affichage(ostream &flux) const{
    flux << H << " " << L << "\n";
    for(int i=0 ; i<H ; i++){
        for(int j=0 ; j<L ; j++){
            if (config[i][j]){
                flux << 'X';
            } else {
                flux << '.';
            }
        }
        flux << "\n";
    }
};

// question 8
jeu_vie::jeu_vie(istream &in){
    in >> H >> L;
    config.resize(H);

    for(int i=0 ; i<H ; i++){
        vector<bool> v(L);
        string line;
        in >> line;
        for(int j=0 ; j<L ; j++){
            v[j] = (line[j]=='X') ? true : false;
        }
        config[i] = v;
    }
};

// question 10
jeu_vie::jeu_vie(int _H, int _L, double p, std::mt19937 &G): H(_H), L(_L), config(H) {
    bernoulli_distribution B(p);

    for(int i=0 ; i<H ; i++){
        vector<bool> v(L);
        for(int j=0 ; j<L ; j++){
            v[j] = B(G);
        }
        config[i] = v;
    }
};

// question 12
int jeu_vie::nb_cellules() const {
    int N=0;

    for(int i=0 ; i<H ; i++){
        for(int j=0 ; j<L ; j++){
            N += config[i][j];
        }
    }

    return N;
};


int main(){
    // question 5
    jeu_vie J(4, 4);
    cout << J.voisins(0, 0) << "\n";
    cout << J.nb_cellules() << "\n";

    // question 8
    ifstream file("planeur.dat");
    jeu_vie J_file(file);
    J_file.affichage(cout);
    cout << "Nb de voisins de (0,0) : " << J_file.voisins(0,0) << ", nb de voisins de (2,1) : " << J_file.voisins(2,1) << "\n";
    cout << "Nb de cellules allumées : " << J_file.nb_cellules() << "\n\n";

    // question 9
    for(int i=0 ; i<20 ; i++){
        J_file.iteration();
        J_file.affichage(cout);
        cout << "\n";
    }

    // question 11
    int H=15;
    int L=25;
    double p=0.3;
    mt19937 G(time(NULL));
    jeu_vie J_alea(H,L,p,G);
    J_alea.affichage(cout);
    for(int i=0 ; i<100 ; i++){
        J_alea.iteration();
    }
    J_alea.affichage(cout);


    // question 13
    vector<double> P{0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9};

    for(double p : P){
        double moyenne = 0.;

        for(int i=0 ; i<100 ; i++){
            jeu_vie J_p(H,L,p,G);
            
            for(int j=0 ; j<100 ; j++)
                J_p.iteration();
            
            moyenne += J_p.nb_cellules();
        }

        cout << "Moyenne pour p=" << p << " : " << moyenne/100 << "\n";
    }

    return 0;
}