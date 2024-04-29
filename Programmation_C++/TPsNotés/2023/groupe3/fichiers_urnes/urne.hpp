//NOM:
//PRENOM:
//# étudiant:

#ifndef URNES_HPP
#define URNES_HPP

// bibliothèques à compléter
#include <array>
#include <numeric>
#include <iostream>
#include <random>

// déclarations à compléter
template <class Entier, int n> class Urne;
template <class Entier, int n>
std::ostream & operator<<(std::ostream &o, const Urne<Entier,n> & U);


// question 1&7
template <class Entier, int n=2>
class Urne {
    private:
        std::array<Entier, n> contenu0;
        std::array<Entier, n> contenu; 

    public:
        // question 1
        Urne();
        // question 2
        int nb_boules() const {     return std::accumulate(contenu.begin(), contenu.end(), 0); };
        // question 3
        double fraction(int j) const {    return double(contenu[j])/nb_boules(); };
        // question 4
        void reset(){   contenu = std::array<Entier,n>(contenu0); };
        // question 5
        friend std::ostream & operator<< <>(std::ostream &o, const Urne<Entier,n> & U);
        // question 8
        template <class Update, class RNG>
        void maj(const Update &f, RNG & G);
        // question 9
        template <class Update, class RNG>
        void maj_p_fois(const Update &f, RNG & G, int p);
};

// question 1
template <class Entier, int n>
Urne<Entier,n>::Urne() {
    std::fill(contenu0.begin(), contenu0.end(), 1);
    std::fill(contenu.begin(), contenu.end(), 1);
};

// question 5
template<class Entier, int n>
std::ostream & operator<<(std::ostream &o, const Urne<Entier,n> & U){
    o << n << "\n";
    for(int i=0 ; i<n ; i++){
        o << U.contenu[i] << "\t";
    }
    o << "\n";
    return o;
};

// question 8
template <class Entier, int n>
template <class Update, class RNG>
void Urne<Entier, n>::maj(const Update &f, RNG & G){
    std::discrete_distribution<int> random_color(contenu.begin(), contenu.end());
    int j = random_color(G);
    f(j, contenu);
};

// question 9
template <class Entier, int n>
template <class Update, class RNG>
void Urne<Entier, n>::maj_p_fois(const Update &f, RNG & G, int p){
    for(int i=0 ; i<p ; i++){
        maj(f, G);
    }
};


#endif
