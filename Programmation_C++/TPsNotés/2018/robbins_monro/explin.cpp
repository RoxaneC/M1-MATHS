#include "explin.hpp"
#include <cmath>

using namespace std;

ExpCombiLin::ExpCombiLin(unsigned _k): k(_k){
    alpha = new double[k];
    beta = new double[k];
    for(int i=0 ; i<k ; i++){
        alpha[i] = 1;
        beta[i] = i;
    }
}

// question 5
double ExpCombiLin::operator()(double x) const {
    double res = 0.;
    for(int i=0 ; i<k ; i++){
        res += alpha[i] * exp(beta[i]*x);
    }
    return res;
}

// question 6
ExpCombiLin::ExpCombiLin(const ExpCombiLin &e): k(e.k){
    alpha = new double[k];
    beta = new double[k];
    for(int i=0 ; i<k ; i++){
        alpha[i] = e.coeff(i);
        beta[i] = e.exponent(i);
    }
}
ExpCombiLin & ExpCombiLin::operator=(const ExpCombiLin &e){
    if(this != &e){
        k = e.k;
        for(int i=0 ; i<k ; i++){
            alpha[i] = e.coeff(i);
            beta[i] = e.exponent(i);
        }
    }
    return *this;
}