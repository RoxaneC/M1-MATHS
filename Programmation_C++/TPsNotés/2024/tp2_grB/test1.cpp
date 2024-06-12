//NOM: CELLIER
//PRENOM: Roxane

//--------    COMPLETER
#include "piecewisefunction.hpp"

#include <cmath>

PiecewiseFn<Segment,Affine_Fn<double>> make_tent_function(double a, double b, double h) {
    //COMPLETER
    // question 8
    PiecewiseFn<Segment,Affine_Fn<double>> PWFn(0.);
    Segment S1(a, (a+b)/2.);
    Segment S2((a+b)/2., b);
    Affine_Fn<double> f1(2*h/(b+a), -2*a*h/(b+a));
    Affine_Fn<double> f2(-2*h/(b+a), 2*b*h/(b+a));
    PWFn.add_piece(S1, f1);
    PWFn.add_piece(S2, f2);
    
    return PWFn;
}

int main() {
	// vérification question 9
    auto Tent = make_tent_function(-1.,3.,5.);
    for(double x=-2.; x<4. ; x += 0.25 ) {
        std::cout << x << ":\t" << Tent(x) << "\n";
    } 
    return 0;
}
