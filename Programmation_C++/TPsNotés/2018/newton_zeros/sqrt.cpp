#ifndef SQRT
#define SQRT    

#include "newton.hpp"
#include <complex>

using namespace std;


// question 6
class Poly2 {
    protected:
        double a;
    public:
        Poly2(double a0): a(a0) {};
        double operator() (double x) const {  return x*x -a; };
        double deriv (double x) const {   return 2*x; };
};

double sqrt_approx(double a, unsigned max_iter, double precision){
    Poly2 P(a);
    return newton_method(P, a, max_iter, precision);
};

// question 7
class Poly2C{
    protected:
        complex<double> a;
    public:
        Poly2C(complex<double> a0): a(a0) {};
        complex<double> operator() (complex<double> x) const {  return x*x -a; };
        complex<double> deriv (complex<double> x) const {   return 2.*x; };
};

complex<double> sqrt_approx_c(complex<double> a, unsigned max_iter, double precision){
    Poly2C PC(a);
    return newton_method(PC, a, max_iter, precision);
};

int main(){
    // no match for ‘operator*’ (operand types are ‘int’ and ‘std::complex<double>’)
    return 0;
}

#endif