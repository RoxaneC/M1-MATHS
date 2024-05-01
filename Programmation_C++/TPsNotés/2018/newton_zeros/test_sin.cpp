#include "newton.hpp"

#include <iostream>

using namespace std;
 
// question 3
class Sinclass {
    public:
        double operator() (double x) const {  return sin(M_PI*x); };
        double deriv (double x) const {   return M_PI*cos(M_PI*x); };
};


int main(){
    // question 4
    Sinclass s;
    for(int i=0 ; i<6 ; i++) cout << newton_method(s, 5.4, i)<< "\n";


    return 0;
}