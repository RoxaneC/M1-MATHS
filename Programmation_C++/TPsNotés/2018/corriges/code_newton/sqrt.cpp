
#include <complex>
#include <iostream>
#include "newton.hpp"

class Poly2 {
	protected:
		double a;
	public:
		Poly2(double a0): a(a0) {}
		double operator () (double x) const { return x*x-a;}
		double deriv (double x) const { return 2.*x;}
};

double sqrt_approx(double a, unsigned n=1000, double precision=1.e-12) {
	Poly2 P(a);
	double resultat = newton_method(P,a,n,precision);
	return resultat;
}

using C= std::complex<double>;
class Poly2C {
	protected:
		C a;
	public:
		Poly2C(C a0): a(a0) {}
		C operator ()(C x) const {return x*x-a;}
		C deriv(C x) const { return 2.*x;}
};

C sqrt_approx_c(C a, unsigned n=1000, double precision= 1.e-12) {
	Poly2C P(a);
	C resultat= newton_method(P,a,n,precision);
	return resultat;
}

int main() {
	double a1=4;
	double a2=9;
	C a3(0.,1.);
	C a4(0.5,-sqrt(3.)/2.);
	std::cout << "Racince de " << a1 << " estimée à : "<< sqrt_approx(a1) << "\n";
	std::cout << "Racince de " << a2 << " estimée à : "<< sqrt_approx(a2) << "\n";
	std::cout << "Racince de " << a3 << " estimée à : "<< sqrt_approx_c(a3) << "\n";
	std::cout << "Racince de " << a4 << " estimée à : "<< sqrt_approx_c(a4) << "\n";
	return 0;
}
