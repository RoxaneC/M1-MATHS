#ifndef ROBMON
#define ROBMON

#include <utility>

// question 1
template <class Func, class DetermSeq, class RandomV, class RNG>
std::pair<double,double> robbins_monro( const Func & h, double x_init, double alpha,
                                        const DetermSeq & epsilon, RandomV & U, RNG & G,
                                        long unsigned N){
    for(int i=0 ; i<N ; i++){
        x_init = x_init - epsilon(i) * (h(x_init) - alpha + U(G));
    }

    return std::make_pair(x_init, h(x_init));
}


#endif