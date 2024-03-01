#include <iostream>
#include <fstream>
#include <random>
using namespace std;

int main() {
    auto f = [](double x) { return 2.*x*x+cos(x/3.)-3.+sqrt(1+x*x)/4. ; };
    auto G = mt19937_64( time(nullptr) );
    auto U = uniform_real_distribution<double>(-0.3,2.6);
    int N  = 27;
    auto os = ofstream("points.dat");
    
    cout << f(0.5) << "\n";
    cout << f(1.) << "\n";
    
    os << N << "\n";
    for (int i = 0; i < N; i++)
    {
        double x= U(G);
        os << x << " "<< f(x) << "\n";
    }
    os.close();
    
    return 0;
}
