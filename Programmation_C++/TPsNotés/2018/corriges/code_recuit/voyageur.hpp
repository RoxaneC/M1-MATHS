#ifndef VOYAGEUR_COMMERCE_CLASS
#define VOYAGEUR_COMMERCE_CLASS

#include <vector>
#include <random>

class DistanceTotale {
protected:
	int M;
	double * dist; // dist[i+M*j] donne la distance entre les villes i et j.
public:
	DistanceTotale(int M0);//alloue le tableau et met les distances à zéro.
	DistanceTotale(const DistanceTotale &);//copie
	~DistanceTotale() { delete [] dist;} 
	DistanceTotale & operator=(const DistanceTotale &);
	//Accesseur et mutateur
	double distance(int i,int j) const { return dist[i+M*j]; }; //accesseur
	double & distance(int i,int j) { return dist[i+M*j]; };	//mutateur
	double operator()(const std::vector<int> & x) const;
};

template <class RNG>
std::vector<int> Y_transposition(const std::vector<int> & x, RNG & G) {
	std::vector<int> y(x);
	std::uniform_int_distribution<int> U(0,y.size()-1);
	std::swap(y[U(G)],y[U(G)]);
	return y;
}
#endif
