#include <iostream>
#include "gradient.hpp"

class Quartic {
	protected:
		double m;
	public:
		Quartic(double m0): m(m0) {}
		double operator() (double x) const { return x*x*x*x-2.*m*m*x*x;}
		double grad(double x) const { return 4.*x*x*x -4.*m*m*x; }
};



int main() {
	Quartic q1(1.);
	Quartic q2(2.);
	
	auto p1=gradient_descent(q1,0.5,1000);
	auto p2=gradient_descent(q2,0.5,1000);
	
	std::cout << "Minimum pour m=1: " << std::get<0>(p1) << "\t(valeur de f: " << std::get<1>(p1) << " et du gradient: "<< std::get<2>(p1)<<")\n";
	std::cout << "Minimum pour m=2: " << std::get<0>(p2) << "\t(valeur de f: " << std::get<1>(p2)<< " et du gradient: "<< std::get<2>(p2)<<")\n";
	
	return 0;
}
