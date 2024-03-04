#include "interpolation.hpp"

#include <iostream>
#include <fstream>

using namespace std;

int main() {
    LagrangeInterpolation P;
    auto is = ifstream("points.dat");
    is >> P;
    cout << "Nombre de points dans P: " << P.nb_points() << "\n";
    cout << "Borne inf: " << P.lower_bound() << "\n";
    cout << "Borne sup: " << P.upper_bound() << "\n";
    cout << "Valeur de P en 0.5 : " << P(0.5) << "\n";  // -1.23435
    cout << "Valeur de P en 1. : " << P(1.) << "\n";  // 0.297851
}
