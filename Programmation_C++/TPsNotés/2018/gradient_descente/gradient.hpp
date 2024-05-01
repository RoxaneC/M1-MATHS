#ifndef GRAD
#define GRAD

#include <tuple>
#include <iostream>

// question 1&2
template <class Func, class V>
std::tuple<V, double, V> gradient_descent(const Func & f, V x0, unsigned max_iter, double lambda=0.01){
    for(int i=0 ; i<max_iter ; i++){
        x0 = x0 + (-lambda)*f.grad(x0);
    }

    std::tuple<V, double, V> t = std::make_tuple(x0, f(x0), f.grad(x0));
    return t;
}

#endif