#include "interpolation.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

vector<double> generate_x(size_t N,double a,double b) {
    auto result=vector<double>(N);
    double delta = (b-a)/N;
    for (size_t i = 0; i < N; i++)
    {
        result[i] = a+ i*delta;
    }
    return result;
}

vector<double> generate_t(size_t N,double a,double b) {
    auto result=vector<double>(N);
    double delta = (b-a)/N;
    for (size_t i = 0; i < N; i++)
    {
        result[i] = a+ (i+0.5)*delta;
    }
    return result;
}

int main() {
    const double a=0.;
    const double b=M_PI;
    for(size_t N : {4, 16, 64, 256, 512, 1024} ){
        auto x = generate_x(N,a,b);
        auto t = generate_t(N,a,b);
        auto y = vector<double>(N);
        transform(
            x.cbegin(),x.cend(),
            y.begin(),
            [](double x){ return sin(x); });
        auto Poly_sin = LagrangeInterpolation(0.,(b-a)/N,y);
        auto yt = vector<double>(N);
        transform(
            t.begin(),t.end(),
            yt.begin(),
            Poly_sin);
        auto dist = vector<double>(N);
        transform(
            y.cbegin(),y.cend(),
            yt.cbegin(),
            dist.begin(),
            [](double y1,double y2) { return std::abs(y1-y2);});
        cout << "N = " << N << " Delta = " << *max_element( dist.begin(),dist.end() ) << "\n";
    }
    return 0;
}
