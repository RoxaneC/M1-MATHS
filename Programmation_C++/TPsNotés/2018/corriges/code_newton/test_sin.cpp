#include "newton.hpp"
#include <cmath>
#include <iostream>

class Sinclass {
	public:
		double operator()(double x) const { return sin(M_PI*x);}
		double deriv (double x) const {return M_PI*cos(M_PI*x);}
};

int main() {
	Sinclass s;
	double x0=5.4;
	double resultat= newton_method(s,x0,5);
	std::cout << "Un zéro est estimé à : " << resultat << " avec une précision " << std::abs(s(resultat)) << ".\n";
}
