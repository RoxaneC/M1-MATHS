#ifndef MY_SANDPILE
#define MY_SANDPILE

// question 1
#include <vector>
#include <list>
#include <utility>
#include <iostream>
#include <algorithm>
#include <random>

using upair=std::pair<unsigned, unsigned>; //raccourci pour les paires d'entiers


class Sandpile{
    private:
        unsigned m; // colonnes
        unsigned n; // lignes
        std::vector<unsigned> terrain;
        std::vector<unsigned> nb_ebouls;
        std::list<upair> next_ebouls;

        // question 9
        void incr_and_test(upair &p);

    public:
        // question 2
        Sandpile(unsigned m0, unsigned n0, unsigned k=4);

        // question 3
        unsigned operator()(int i, int j) const { return terrain[i+j*m]; };

        // question 4
        friend std::ostream & operator<<(std::ostream &out, const Sandpile &s);

        // question 6
        unsigned h(upair &p) const {    return terrain[p.first+p.second*m]; };
        void h(upair &p, unsigned k) {    terrain[p.first+p.second*m] = k; };

        // question 7
        std::list<upair> voisins(upair p) const;

        // question 10
        void eboul(upair &p);

        // question 11
        int stabil();

        // question 12
        int nb_total_ebouls() const;

        // question 15
        int add_random_grain(std::mt19937 &G, int k=1);

        // question 17
        friend Sandpile operator+(const Sandpile &S1, const Sandpile &S2);

        // question 19
        unsigned volume_total() const {  return std::accumulate(terrain.begin(), terrain.end(), 0);};
};

#endif