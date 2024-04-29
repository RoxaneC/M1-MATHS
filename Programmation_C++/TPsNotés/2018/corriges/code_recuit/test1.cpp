#include "recuit.hpp"
#include <iostream>
#include <random>

int main() {
//Question 1: déclarations

	std::mt19937 Gerard(time(nullptr));
	
	auto phi = [](const double & x) { double y=x*x; return y*y*y-48.*y; };
	
	auto temp= [](long unsigned n)->double { return 10.*exp(n*log(0.9));};
	//auto temp= [](long unsigned n)->double { return 10.*pow(0.9,n);};
	
	auto y_norm = [](const double & x, std::mt19937 & G) {
		std::normal_distribution<double> N(0.,1.); 
		return x+N(G);
	};
	int N=1000;
	
	
// Question 2: une première estimation
	double x_estim = recuit_simule(phi,0.,temp,y_norm,Gerard,N);
	std::cout << "Estimation d'un minimum: " << x_estim << "\n---------------- \n";
	
// Question 3:
	int K=100;
	double m,v;
	
{	// POUR N=500;
	N=200;
	m=0.;
	v=0.;
	for (int i = 0; i < K; i++)
	{
		x_estim = std::abs(recuit_simule(phi,0.,temp,y_norm,Gerard,N));
		m += x_estim;
		v += x_estim*x_estim;
	}
	m /= double(K);
	v /= double(K);
	std::cout << "Estimation pour N=" << N << " avec " << K << " échantillons de |x| :\n";
	std::cout << "\tM= " << m << "\n";
	std::cout << "\tV= " << v-m*m << "\n";
	std::cout << "\n---------------- \n";
}
{	// POUR N=1000;
	N=400;
	m=0.;
	v=0.;
	for (int i = 0; i < K; i++)
	{
		x_estim = std::abs(recuit_simule(phi,0.,temp,y_norm,Gerard,N));
		m += x_estim;
		v += x_estim*x_estim;
	}
	m /= double(K);
	v /= double(K);
	std::cout << "Estimation pour N=" << N << " avec " << K << " échantillons de |x| :\n";
	std::cout << "\tM= " << m << "\n";
	std::cout << "\tV= " << v-m*m << "\n";
	std::cout << "\n---------------- \n";
}

	
}
