#ifndef MY_PI
#define MY_PI

#include <random>

class SquareInDisk{
	private:
		std::uniform_real_distribution<double> U;
	public:
		// question 5.2
		SquareInDisk(): U(0,1){};
		// question 5.3
		template <class RNG>
		double operator()(RNG & G);
};

template <class RNG>
double SquareInDisk::operator()(RNG &G){
	double X = U(G);
	double Y = U(G);
	
	return X*X + Y*Y <= 1.;
};

#endif
