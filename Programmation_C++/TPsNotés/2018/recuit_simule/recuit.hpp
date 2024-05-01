#ifndef REC
#define REC

#include <random>
#include <cmath>

// question 1
template <class E, class Func, class TempSeq, class RandomY, class RNG>
E recuit_simule(const Func & phi, E x0, const TempSeq & T, const RandomY & Y, RNG & G, long unsigned N){
    std::uniform_real_distribution U(0.,1.);
    for(int i=0 ; i<N ; i++){
        E y = Y(x0, G);
        if ( U(G) <= std::min(1., std::exp( (phi(x0)-phi(y)) /T(i) )) ){
            x0 = y;
        }
    }
    return x0;
}




#endif