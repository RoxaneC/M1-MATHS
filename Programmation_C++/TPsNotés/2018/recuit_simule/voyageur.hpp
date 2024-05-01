#ifndef VOYAGE
#define VOYAGE

#include <vector>
#include <random>

// quesyion 5
class DistanceTotale {
    protected:
        int M;
        double * dist; // dist[i+M*j] donne la distance entre les villes i et j.
    public:
        DistanceTotale(int M0);//alloue le tableau et met les distances à zéro.
        //Accesseur et mutateur
        double distance(int i,int j) const;
        double & distance(int i,int j);
        double operator()(const std::vector<int> & x) const;

        // question 7
        DistanceTotale(const DistanceTotale & DT);
        DistanceTotale & operator=(const DistanceTotale & DT);
};


template <class RNG>
std::vector<int> Y_transposition(const std::vector<int> & x, RNG & G) {
    std::vector<int> y(x);
    std::uniform_int_distribution<int> U(0,y.size()-1);
    std::swap(y[U(G)],y[U(G)]);
    return y;
}

#endif