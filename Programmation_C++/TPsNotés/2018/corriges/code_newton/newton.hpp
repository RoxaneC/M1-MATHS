#ifndef NEWTON_TEMPLATE
#define NEWTON_TEMPLATE

#include <cstdlib>

template <class Func, class K>
K newton_method(const Func & f, K x0, unsigned max_iter, double precision= 1.e-12) {
	K x(x0);
	K fval=f(x);
	K fder=f.deriv(x);
	unsigned iter=0;
	while( (iter < max_iter) && ( std::abs(fval) > precision) ) {
		++iter;
		x -= fval/fder;
		fval = f(x);
		fder = f.deriv(x);
	}
	return x;
}
#endif
