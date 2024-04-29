#include "recuit.hpp"
#include "voyageur.hpp"
#include <vector>
#include <iostream>
#include <random>
#include <cmath>

int main() {
	std::mt19937 Gerard(time(nullptr));
	
	const int M=50;
	DistanceTotale D(M);
	//~ for (int i = 0; i < M; i++)
	//~ {
		//~ double xi=0.5*cos(i)+cos(M_PI*(1+2*i)/4.);
		//~ double yi=0.5*sin(i)+sin(M_PI*(1+2*i)/4.);
		//~ for (int j = 0; j < M; j++)
		//~ {
			//~ double xj=0.5*cos(j)+cos(M_PI*(1+2*j)/4.);
			//~ double yj=0.5*sin(j)+sin(M_PI*(1+2*j)/4.);
			//~ double dxij=xi-xj;
			//~ double dyij=yi-yj;
			//~ D.distance(i,j) = sqrt( dxij*dxij+dyij*dyij);
		//~ }
	//~ }
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < M; j++)
		{
			double r=cos(4*i+3*j);
			D.distance(i,j)=r*r;
		}
		
	}
	

	
	auto temp = [](long unsigned n) { return 10*exp(n*log(0.95));};

	
	std::vector<int> itineraire0(M);
	for (int i = 0; i < M; i++)
	{
		itineraire0[i]=i;
	}
	std::cout << "\nDistance totale parcourue sur la config initiale: " << D(itineraire0) << "\n";
	
	long unsigned N=100000;
	std::vector<int> itineraire = recuit_simule(D,itineraire0,temp,Y_transposition<std::mt19937>,Gerard,N);

	
	std::cout << "\nTrajectoire obtenue:\n\t";
	for (int i = 0; i < M; i++)
	{
		std::cout << itineraire[i] << " ";
	}
	std::cout << "\nDistance totale parcourue: " << D(itineraire) << "\n";
	
	return 0;
}
