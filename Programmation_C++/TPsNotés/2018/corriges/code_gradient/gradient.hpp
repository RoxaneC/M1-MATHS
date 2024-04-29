 #ifndef GRADIENT_TEMPLATE 
 #define GRADIENT_TEMPLATE
 
#include <tuple> 

template <class Func, class V>
std::tuple<V,double,V> gradient_descent(const Func & f, V x0, 
		unsigned max_iter, double lambda= 0.01) 
{
	V x(x0);
	double fval = f(x);
	V fgrad = f.grad(x);
	
	for (unsigned iter = 0; iter < max_iter; ++iter)
	{
		x = x+(-lambda)*fgrad;
		fval = f(x);
		fgrad = f.grad(x);
	}
	
	return std::make_tuple(x,fval,fgrad);
}
 
 #endif
