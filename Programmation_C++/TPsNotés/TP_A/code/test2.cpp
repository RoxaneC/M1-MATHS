#include <iostream>
#include <fstream>
#include "interpolation.hpp"
using namespace std;
int main() {
    LagrangeInterpolation P;
    auto is = ifstream("points.dat");
    is >> P;
    cout << "Nombre de points dans P: " << P.nb_points() << "\n";
    cout << "Borne inf: " << P.lower_bound() << "\n";
    cout << "Borne sup: " << P.upper_bound() << "\n";
    cout << "Valeur de P en 0.5 : " << P(0.5) << "\n";
    cout << "Valeur de P en 1. : " << P(1.) << "\n";
}
