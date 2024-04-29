#ifndef ROBBINSMONRO_TEMPLATE
#define ROBBINSMONRO_TEMPLATE
#include <utility>
template <class Func, class DetermSeq, class RandomV, class RNG>
std::pair<double,double> robbins_monro(
		const Func & h, double x_init, double alpha, 
		const DetermSeq & epsilon,RandomV & U, RNG & G,
		long unsigned N) 
{
	double x(x_init);
	for (long unsigned i = 0; i < N; ++i)
	{
		x -= epsilon(i)*(h(x)-alpha+U(G));
	}
	return std::make_pair(x,h(x));
}

#endif
