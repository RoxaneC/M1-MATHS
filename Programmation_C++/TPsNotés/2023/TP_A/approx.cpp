#include "interpolation.hpp"

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// question 12
vector<double> generate_x(int N){
    vector<double> x(N);

    for(int k=0 ; k<N ; k++){
        x[k] = M_PI*double(k)/N;
    }

    return x;
};

vector<double> generate_t(int N){
    //
    vector<double> t(N);

    for(int k=0 ; k<N ; k++){
        t[k] = M_PI*double(2*k+1)/(2*N);
    }

    return t;
};

// question 13
int main(){
    //
    vector<int> N{4, 16, 64, 256, 512}; //

    for(int n : N){
        vector<double> x = generate_x(n);
        vector<double> t = generate_t(n);

        LagrangeInterpolation P;
        for(int i=0 ; i<n ; i++){
            P.add_point( x[i], sin(x[i]) );
        }

        vector<double> vect_delta(n);
        for(int i=0 ; i<n ; i++){
            vect_delta[i] = abs(sin(t[i]) - P(t[i]));
        }

        double delta = *max_element(vect_delta.begin(), vect_delta.end());
        cout << "Le delta pour n = " << n << " est : " << delta << "\n";

        // delta devrai tendre vers 0 puisqu'on cherche à approximer notre fonction
    }

    return 0;
}