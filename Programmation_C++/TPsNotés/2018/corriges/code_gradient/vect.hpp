#ifndef VECT_TEMPLATE_CLASS
#define VECT_TEMPLATE_CLASS

#include <iostream>

template <unsigned d> 
class Vect {
	protected:
		double * coord;
	public:
		Vect();
		double operator[](unsigned i) const { return coord[i];}
		double  & operator[](unsigned i) { return coord[i];}
		// Rule of three:
		Vect(const Vect &);
		~Vect() { delete [] coord;}
		Vect<d> & operator=( const Vect<d> &);
};

template <unsigned d>
std::ostream & operator<<( std::ostream & o, const Vect<d> & v) {
	o << "(";
	for (unsigned i = 0; i < d-1; i++) o << v[i] << ",";
	o << v[d-1] << ")";
	return o;
}

template <unsigned d>
Vect<d>::Vect(): coord(nullptr) {
	coord = new double[d];
	for (unsigned i = 0; i < d; ++i)
	{
		coord[i]=0.;
	}
}

template <unsigned d>
Vect<d>::Vect(const Vect<d> & v): coord(nullptr) {
	coord = new double[d];
	for (unsigned i = 0; i < d; i++) coord[i]=v.coord[i];
}

template <unsigned d>
Vect<d> & Vect<d>::operator = (const Vect<d> & v) {
	if( this != &v ) {
		for (unsigned i = 0; i < d; i++) coord[i]=v.coord[i];
	}
	return *this;
}

template <unsigned d>
Vect<d> operator*(double x,const Vect<d> & u) {
	Vect<d> xu;
	for (unsigned i = 0; i < d; i++) xu[i]=x*u[i];
	return xu;
}

template <unsigned d>
Vect<d> operator+(const Vect<d> & u1,const Vect<d> & u2) {
	Vect<d> s;
	for (unsigned i = 0; i < d; i++) s[i]=u1[i]+u2[i];
	return s;
}



#endif
