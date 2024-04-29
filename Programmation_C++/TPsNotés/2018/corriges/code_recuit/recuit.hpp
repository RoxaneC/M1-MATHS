#ifndef RECUIT_SIMULE_TEMPLATE
#define RECUIT_SIMULE_TEMPLATE

#include <random>
#include <iostream>
template <class E,class Func, class TempSeq, class RandomY, class RNG>
E recuit_simule(const Func & phi, E x0, const TempSeq & T,
		const RandomY & Y,RNG & G, long unsigned N) 
{
	E x(x0),y;
	double phi_new,phi_old=phi(x);
	double u;
	std::uniform_real_distribution<double> U(0.,1.);
	for (long unsigned i = 0; i < N; i++)
	{
		y=Y(x,G);
		phi_new=phi(y);
		u=U(G);
		if( u < exp( (phi_old-phi_new)/T(i) ) ) {
			x=y;
			phi_old=phi_new;
		}
	}
	return x;
}

#endif
