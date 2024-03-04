#include "interpolation.hpp"

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

// question 2
LagrangeInterpolation::LagrangeInterpolation(double _u, double _delta, const vector<double> &_y): x_values(_y.size()), y_values(_y){
    //
    for(int i=0 ; i<_y.size() ; i++){
        x_values[i] = _u + i*_delta;
    }
};

// question 3
ostream & operator<<(std::ostream &out, const LagrangeInterpolation &LI){
    out << LI.x_values.size() << "\n";
    for(int i=0 ; i<LI.x_values.size() ; i++){
        out << LI.x_values[i] << " " << LI.y_values[i] << "\n";
    }

    return out;
};

// question 6
double LagrangeInterpolation::operator()(double x) const{
    double result = 0.;

    for(int j=0 ; j<x_values.size() ; j++){
        double Rj = 1.;
        for(int i=0 ; i<x_values.size() ; i++){
            if (i != j)     Rj *= (x-x_values[i])/(x_values[j]- x_values[i]);
        }
        result += y_values[j]*Rj;
    }

    return result;
};

// question 7
bool LagrangeInterpolation::add_point(double x, double y){
    if( find(x_values.begin(), x_values.end(), x) != x_values.end() ) {
        cout << "La valeur " << x << " est déjà présente dans le vecteur x.\n";
        return false;
    } else {
        x_values.push_back(x);
        y_values.push_back(y);
        return true;
    }
};

// *****************************  PARTIE 3  *******************************
// question 9
LagrangeInterpolation::LagrangeInterpolation(): x_values({}), y_values({}){};

// question 10
istream & operator>>(std::istream &in, LagrangeInterpolation &LI){
    //
    int taille;
    in >> taille;

    double x; double y;
    while(in >> x >> y){
        LI.add_point(x,y);
    }

    return in;
    };

// question 14
LagrangeInterpolation operator+(const LagrangeInterpolation &L1, const LagrangeInterpolation &L2){
    //
    int N1 = L1.x_values.size();
    int N2 = L2.x_values.size();
    
    vector<double> x_res(N1+N2);
    vector<double> y_res(N1+N2);

    //
    copy(  L1.x_values.begin(), L1.x_values.end(), x_res.begin());
    copy(  L1.y_values.begin(), L1.y_values.end(), y_res.begin());
    /*transform(  y_res.begin(), y_res.end(), y_res.begin(),
                [L2, x_res, y_res](double i){ return i+L2(x_res[.....] ); });


    //
    copy(  L2.x_values.begin(), L2.x_values.end(), x_res.begin()+N1);
    copy(  L2.y_values.begin(), L2.y_values.end(), y_res.begin()+N1);
    transform(  y_res.begin(), y_res.end(), y_res.begin(),
                [L1, x_res](double i){ return i+L1(x_res[.....]); }); */

    LagrangeInterpolation Res;
    copy(x_res.begin(), x_res.end(), back_inserter(Res.x_values));
    copy(y_res.begin(), y_res.end(), back_inserter(Res.y_values));

    return Res;
};
