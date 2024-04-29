#include <iostream>
#include "gradient.hpp"
#include "vect.hpp"

class GG {
	public:
		double operator()(const Vect<2> & u) const { 
			double x2=u[0]*u[0];
			double x4=x2*x2;
			double y2=u[1]*u[1];
			double y4=y2*y2;
			return x4+y4-2.*x2-2.*y2+u[0]+u[1];
		}
		Vect<2> grad(const Vect<2> & u) const {
			Vect<2> res;
			res[0]=4*u[0]*u[0]*u[0]-4*u[0]+1.;
			res[1]=4*u[1]*u[1]*u[1]-4*u[1]+1.;
			return res;
		}
};

int main() {
	auto p = gradient_descent(GG(),Vect<2>(),200);
	std::cout << "Minimum en " << std::get<0>(p) << " avec valeur de G " << std::get<1>(p) << " et du gradient "<< std::get<2>(p)<< "\n";
}
