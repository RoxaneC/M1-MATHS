#include "voyageur.hpp"

using namespace std;

// question 5
DistanceTotale::DistanceTotale(int M0): M(M0){
    dist = new double[M];
    for(int i=0 ; i<M ; i++){
        dist[i] = 0.;
    }
}
double DistanceTotale::distance(int i,int j) const{
    return dist[i+M*j];
}
double & DistanceTotale::distance(int i,int j){
    return dist[i+M*j];
}

// question 6
double DistanceTotale::operator()(const std::vector<int> & x) const{
    double res = 0.;
    for(int i=0 ; i<x.size()-1 ; i++){
        res += dist[x[i], x[i+1]];
    }
    return res;
}

// question 7
DistanceTotale::DistanceTotale(const DistanceTotale & DT){
    M = DT.M;
    dist = new double[M];
    for(int i=0 ; i<M ; i++){
        dist[i] = DT.dist[i];
    }
}
// CORRECTION
DistanceTotale & DistanceTotale::operator=(const DistanceTotale & D) {
	if( this != &D) {
		if( M != D.M) {
			M=D.M;
			dist = new double[M*M];
		}
		for (int k = 0; k < M*M; ++k)
		{
			dist[k]= D.dist[k];
		}
	}
	return *this;
}