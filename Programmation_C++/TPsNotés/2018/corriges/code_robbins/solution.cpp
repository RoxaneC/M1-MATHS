#include "robbinsmonro.hpp"
#include "explin.hpp"
#include <iostream>
#include <random>

int main() {
	ExpCombiLin h(3);
	h.coeff(1)=3.;
	std::cout << h(0.) << "\n";
	std::cout << h(1.) << "\n";
	
	double alpha=3.;
	std::normal_distribution<double> N(0.,0.1);
	std::mt19937 Gerard(time(nullptr));
	
	auto eps1=[](long unsigned n){ return 0.1/(n+1.);};
	auto eps2=[](long unsigned n){ return 0.75/(n+1.);};
	auto eps3=[](long unsigned n){ return 1./(n+1.);};
	
	long unsigned iter=1000;
	
	auto p1=robbins_monro(h,0.,alpha,eps1,N,Gerard,iter);
	auto p2=robbins_monro(h,0.,alpha,eps2,N,Gerard,iter);
	auto p3=robbins_monro(h,0.,alpha,eps3,N,Gerard,iter);
	
	std::cout << "Cas 1: " << p1.first << " (" << p1.second << ")"<<"\n";
	std::cout << "Cas 2: " << p2.first << " (" << p2.second << ")"<< "\n";
	std::cout << "Cas 3: " << p3.first << " (" << p3.second << ")"<< "\n";
	
	
}
