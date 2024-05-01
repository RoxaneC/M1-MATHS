#ifndef NEWT
#define NEWT

#include <cmath>
#include <complex>

// question 1&2
template <class Func, class K>
K newton_method(const Func & f, K x0, unsigned max_iter, double precision=1e-12){
    for(int i=0 ; i<max_iter && std::abs(f(x0))>precision ; i++){
        x0 = x0 - f(x0)/f.deriv(x0);
    }
    return x0;
}




#endif