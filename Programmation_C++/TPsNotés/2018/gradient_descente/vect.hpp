#ifndef VECT
#define VECT

#include <iostream>
#include <algorithm>

template <unsigned d> class Vect;
template <unsigned d> std::ostream & operator<<(std::ostream &o, const Vect<d> &v);
template <unsigned d> Vect<d> operator*(double x, const Vect<d> & u);
template <unsigned d> Vect<d> operator+(const Vect<d> & u1, const Vect<d> & u2);


template <unsigned d>
class Vect {
    protected:
        double * coord;//tableau dynamique avec d cases
    public:
        // question 5
        Vect();
        double operator[](unsigned i) const {   return coord[i]; }; //accesseur à la i-ème coordonnée
        double & operator[](unsigned i) {   return coord[i]; }; //mutateur à la i-ème coordonnée
        friend std::ostream & operator<< <>(std::ostream &o, const Vect<d> &v);

        // question 7
        Vect(const Vect<d> &v);

        // question 8
        friend Vect<d> operator* <>(double x, const Vect<d> & u);
        friend Vect<d> operator+ <>(const Vect<d> & u1, const Vect<d> & u2);

        // CORRECTION
        Vect<d> & operator=( const Vect<d> &);

};

// question 5
template <unsigned d>
Vect<d>::Vect() {
    coord = new double[d];
    for(int i=0 ; i<d ; i++){
        coord[i] = 0.;
    }
}

// question 6
template <unsigned d>
std::ostream & operator<<(std::ostream &o, const Vect<d> &v){
    o << "(";
    for(int i=0 ; i<d-1 ; i++){
        o << v[i] << ", ";
    }
    o << v[d-1] << ")";

    return o;
}

// question 7
template <unsigned d>
Vect<d>::Vect(const Vect<d> &v) {
    coord = new double[d];
    for(int i=0 ; i<d ; i++){
        coord[i] = v[i];
    }
}

// question 8
template <unsigned d>
Vect<d> operator*(double x, const Vect<d> & u){
    Vect<d> v_res(u);
    for(int i=0 ; i<d ; i++){
        v_res[i] *= x; 
    }
    return v_res;
}
template <unsigned d>
Vect<d> operator+(const Vect<d> & u1, const Vect<d> & u2){
    Vect<d> v_res(u1);

    for(int i=0 ; i<d ; i++){
        v_res[i] += u2[i];
    }

    return v_res;
}


// CORRECTION
template <unsigned d>
Vect<d> & Vect<d>::operator=(const Vect<d> & v) {
	if( this != &v ) {
		for (unsigned i = 0; i < d; i++) coord[i]=v[i];
	}
	return *this;
}


#endif