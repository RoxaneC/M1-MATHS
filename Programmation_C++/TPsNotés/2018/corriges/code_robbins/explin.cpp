#include "explin.hpp"
#include <cmath>

ExpCombiLin::ExpCombiLin(unsigned k0): k(k0), alpha(nullptr), beta(nullptr) {
	alpha = new double[k0];
	beta = new double[k0];
	for (int i = 0; i < k; ++i)
	{
		alpha[i]=1.;
		beta[i]=i;
	}
}

ExpCombiLin::ExpCombiLin(const ExpCombiLin & E): k(E.k), alpha(nullptr), beta(nullptr) {
	alpha = new double[k];
	beta = new double[k];
	for (int i = 0; i < k; ++i)
	{
		alpha[i]=E.alpha[i];
		beta[i]=E.beta[i];
	}
}

ExpCombiLin & ExpCombiLin::operator =(const ExpCombiLin & E) {
	if( this != &E) {
		if( k != E.k ) {
			k=E.k;
			delete []alpha;
			delete []beta;
			alpha= new double[k];
			beta = new double[k];
		}
		for (int i = 0; i < k; ++i)
		{
			alpha[i]=E.alpha[i];
			beta[i]=E.beta[i];
		}
	}
	return *this;
}

double ExpCombiLin::operator ()(double x) const {
	double s=0.;
	for (int i = 0; i < k; i++)
	{
		s += alpha[i]*exp(beta[i]*x);
	}
	return s;
}
