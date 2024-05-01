#include "recuit.hpp"

#include <cmath>
#include <iostream>

using namespace std;


int main(){
    // question 2
    auto phi = [](const double &x){    return pow(x,6) - 48*x*x; };
    auto T = [](long unsigned n){   return 10*pow(0.9, n); };
    auto Y = [](const double &x, mt19937 & G){  return x + normal_distribution<double>(0.,1.)(G);};

    // question 3
    mt19937 Gen(time(nullptr));
    cout << "Q3)\tEstimation de phi : " << recuit_simule(phi, 0, T, Y, Gen, 1000) << "\n";

    // question 4
    int K = 100;
    double mean200 = 0.;    double mean400 = 0.;
    double var200 = 0.; double var400 = 0.;
    for(int k=0 ; k<K ; k++){
        double res = recuit_simule(phi, 0, T, Y, Gen, 200);
        mean200 += abs(res)/K;
        var200 += abs(res)*abs(res)/K;
        res = recuit_simule(phi, 0, T, Y, Gen, 400);
        mean400 += abs(res)/K;
        var400 += abs(res)*abs(res)/K;
    }
    var200 -= mean200*mean200;
    var400 -= mean400*mean400;
    cout << "Q4)\tPour N=200, Moyenne : " << mean200 << ", Variance : " << var200 << "\n";
    cout << "\tPour N=400, Moyenne : " << mean400 << ", Variance : " << var400 << "\n";


    return 0;
}