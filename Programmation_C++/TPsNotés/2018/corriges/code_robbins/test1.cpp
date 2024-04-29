#include <random>
#include <iostream>
#include "robbinsmonro.hpp"

//double h(double x) { return 1./(1.+exp(-x)); }


int main() {
	auto h=[](double x) { return 1./(1.+exp(-x)); };
	double alpha=2./3.;
	auto epsilon=[](long unsigned n) { return 1./(n+1.);};
	std::uniform_real_distribution<double> U(-0.1,0.1);
	std::mt19937 G(time(nullptr));
	std::pair<double,double> p;
	long unsigned N;
	

	N=1000000;
	p = robbins_monro(h,0.,alpha,epsilon,U,G,N);
	std::cout << "Pour N= " << N <<", on obtient par exemple x= "<<p.first<<" (et h(x)= " << p.second << ")\n";
	
	N=10000000;
	p = robbins_monro(h,0.,alpha,epsilon,U,G,N);
	std::cout << "Pour N= " << N <<", on obtient par exemple x= "<<p.first<<" (et h(x)= " << p.second << ")\n";
	
	double m;
	double v;
	int K=100;
	
	N=100000;
	m=0.;
	v=0.;
	for (int i = 0; i < K; i++)
	{
		p=robbins_monro(h,0.,alpha,epsilon,U,G,N);
		m += p.first;
		v += p.first*p.first;
	}
	m /= double(K);
	v /= double(K);
	std::cout << "Moyennes et variances empiriques pour N= " << N << ":\n";
	std::cout << "\t Moy= " << m << "\n";
	std::cout << "\t Var= " << v-m*m << "\n";
	std::cout << "------------------\n";
	
	N=1000000;
	m=0.;
	v=0.;
	for (int i = 0; i < K; i++)
	{
		p=robbins_monro(h,0.,alpha,epsilon,U,G,N);
		m += p.first;
		v += p.first*p.first;
	}
	m /= double(K);
	v /= double(K);
	std::cout << "Moyennes et variances empiriques pour N= " << N << ":\n";
	std::cout << "\t Moy= " << m << "\n";
	std::cout << "\t Var= " << v-m*m << "\n";
	std::cout << "------------------\n";
	
	
	return 0;
}
