#ifndef MY_GAME_LIFE
#define MY_GAME_LIFE

#include <vector>
#include <iostream>
#include <random>

// question 1
class jeu_vie{
    private:
        int H, L;
        std::vector<std::vector<bool>> config;

    public:
        jeu_vie(int _H, int _L);

        // question 3
        int hauteur() const {   return H; };
        int largeur() const {   return L; };

        // question 4
        int voisins(int i, int j) const;

        // question 6
        void iteration();

        // question 7
        void affichage(std::ostream &flux) const;

        // question 8
        jeu_vie(std::istream &in);

        // question 10
        jeu_vie(int _H, int _L, double p, std::mt19937 &G);

        // question 12
        int nb_cellules() const;

};

#endif