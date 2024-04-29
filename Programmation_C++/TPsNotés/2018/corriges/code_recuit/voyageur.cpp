#include "voyageur.hpp"

DistanceTotale::DistanceTotale(int M0): M(M0), dist(nullptr) {
	dist = new double[M0*M0];
	for (int k = 0; k < M0*M0; ++k)
	{
		dist[k]=0.;
	}
}

//constructeur par copie:
DistanceTotale::DistanceTotale(const DistanceTotale & D): M(D.M), dist(nullptr) {
	dist = new double[M*M];
	for (int k = 0; k < M*M; ++k)
	{
		dist[k] = D.dist[k];
	}
}

//affectation
DistanceTotale & DistanceTotale::operator =(const DistanceTotale & D) {
	if( this != &D) {
		if( M != D.M) {
			M=D.M;
			delete [] dist;
			dist = new double[M*M];
		}
		for (int k = 0; k < M*M; ++k)
		{
			dist[k]= D.dist[k];
		}
	}
	return *this;
}

double DistanceTotale::operator ()(const std::vector<int> & x) const {
	double dist_tot=0.;
	for (size_t i = 0; i < x.size()-1; i++)
	{
		dist_tot += distance(x[i],x[i+1]);
	}
	return dist_tot;
}
