#include "explin.hpp"
#include "robbinsmonro.hpp"

#include <random>
#include <iostream>

using namespace std;

int main(){
    ExpCombiLin e(3);
    e.coeff(0) = 1;    e.coeff(1) = 3;    e.coeff(2) = 1;
    e.exponent(0) = 0;    e.exponent(1) = 1;    e.exponent(2) = 2;
    mt19937 Gen(time(nullptr));
    normal_distribution<double> N(0.,0.1);
    auto eps1 = [](long unsigned n){     return 0.1/(n+1.); };
    auto eps2 = [](long unsigned n){     return 0.75/(n+1.); };
    auto eps3 = [](long unsigned n){     return 1./(n+1.); };

    pair<double,double> p = robbins_monro(e, 0., 3., eps1, N, Gen, 1000);
    cout << "N = " << 1000 << ", on obtient x = " << p.first << " (h(x) = " << p.second << ")\n" ;
    p = robbins_monro(e, 0., 3., eps2, N, Gen, 1000);
    cout << "N = " << 1000 << ", on obtient x = " << p.first << " (h(x) = " << p.second << ")\n" ;
    p = robbins_monro(e, 0., 3., eps3, N, Gen, 1000);
    cout << "N = " << 1000 << ", on obtient x = " << p.first << " (h(x) = " << p.second << ")\n" ;

    return 0;
}