#include "fma.hpp"
#include "geometry.hpp"

#include <numeric>
#include <cmath>

using namespace std;

// question 3
template <class E>
double Finite_atomic_measure<E>::total_mass() const {
    double res = accumulate(    mass.begin(), mass.end(), 0.,
                                [](double d, const pair<E, double> &p){   return d + p.second; } );

    return res;
}

// question 5
template <class E>
ostream & operator<<(ostream &o, const Finite_atomic_measure<E> &fam){
    o << fam.nb_of_atoms() << "\n";
    for(const pair<E, double> &p: fam.mass){
        o << p.first << "\t" << p.second << "\n";
    }

    return o;
}

// question 7
template <class E>
template <class Domain>
double Finite_atomic_measure<E>::measure(const Domain & D) const{
    double res = accumulate(    mass.begin(), mass.end(), 0.,
                                [D](double d, const pair<E, double> &p){   return (D.contains(p.first)) ? d + p.second : d; } );
    return res;
}

// question 10
template <class E>
template <class RealFunction_on_E>
double Finite_atomic_measure<E>::integral(const RealFunction_on_E & f) const{
    double res = accumulate(    mass.begin(), mass.end(), 0.,
                                [f](double d, const pair<E, double> &p){   return d + p.second*f(p.first); } );
    return res;
}

// question 11
template <class E>
istream & operator>>(istream &i, Finite_atomic_measure<E> &fam){
    fam.mass.clear();

    int n;
    i >> n;

    E x; double d;
    while(i >> x >> d){
        fam.mass[x] += d;
    }
    return i;
}

// question 13
template < class E1, class Function >  
Finite_atomic_measure<invoke_result_t< Function, E1> > image(const Finite_atomic_measure<E1> & mu, const Function & f){
    Finite_atomic_measure<invoke_result_t< Function, E1> > nu;
    for(const pair<E1, double> &p : mu.get_mass()){
        nu.add_mass(f(p.first), p.second);
    }
    return nu;
}

// BONUS : question 18
template <class E>
Finite_atomic_measure<E> operator+(const Finite_atomic_measure<E> & fam1, const Finite_atomic_measure<E> & fam2){
    Finite_atomic_measure<E> res = fam1;
    for(const pair<E, double> &p : fam2.mass){
        res.add_mass(p.first, p.second);
    }

    return res;
}
