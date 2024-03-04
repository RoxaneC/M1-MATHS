#include "interpolation.hpp"

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

int main(){
    //
	LagrangeInterpolation P(0., 0.25,{1., 3., 2., 4.});
    LagrangeInterpolation Q(0., 0.25,{1., 3., 2., 4.});
    
    std::cout << (P + Q);

    return 0;
}