#ifndef QUARTIC
#define QUARTIC

#include <cmath>

// question 3
template <class V>
class Quartic {
    protected:
        double m;
    public:
        Quartic(double m0): m(m0){};
        V operator()(const V x) const {   return pow(x,4)- 2*m*m*x*x; };
        V grad(const V x) const {   return 4*pow(x,3)- 4*m*m*x; } 
};

#endif