#include "robbinsmonro.hpp"

#include <cmath>
#include <random>
#include <vector>
#include <iostream>

using namespace std;

int main(){
    // question 2
    auto f1 = [](double x){ return 1./(1. + exp(-x)); };
    auto eps = [](long unsigned n){     return 1./(n+1.); };
    mt19937 Gen(time(nullptr));
    uniform_real_distribution<double> U(-0.1, 0.1);
    int N = 1000000;
    pair<double,double> p1 = robbins_monro(f1, 0., 2./3., eps, U, Gen, N);
    cout << "N = " << N << ", on obtient x = " << p1.first << " (h(x) = " << p1.second << ")\n" ;
    N = 10000000;
    pair<double,double> p2 = robbins_monro(f1, 0., 2./3., eps, U, Gen, N);
    cout << "N = " << N << ", on obtient x = " << p2.first << " (h(x) = " << p2.second << ")\n\n" ;

    // question 3
    int K = 100;
    double mean1 = 0.;    double mean2 = 0.;
    double var1 = 0.;    double var2 = 0.;

    for(int k=0 ; k<K ; k++){
        p1 = robbins_monro(f1, 0., 2./3., eps, U, Gen, 1000000);
        p2 = robbins_monro(f1, 0., 2./3., eps, U, Gen, 10000000);
        mean1 += p1.first/double(K);
        mean2 += p2.first/double(K);
        var1 += p1.first*p1.first /double(K);
        var2 += p2.first*p2.first /double(K);
    }
    var1 -= mean1*mean1;
    var2 -= mean2*mean2;

    cout << "N = " << 1000000 << ", Moyenne = " << mean1 << ", Variance = " << var1 << "\n";
    cout << "N = " << 10000000 << ", Moyenne = " << mean2 << ", Variance = " << var2 << "\n";
    
    return 0;
}