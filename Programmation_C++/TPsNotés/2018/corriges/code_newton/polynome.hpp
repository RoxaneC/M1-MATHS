#ifndef POLYNOME_CLASS
#define POLYNOME_CLASS

#include <vector>

template <class K>
class Polynome {
	protected: 
		int degree;
		K * coeff;
	public:
		Polynome(const std::vector<K> & v);
		// Rule of three:
		Polynome(const Polynome &);
		~Polynome() { delete [] coeff;}
		Polynome & operator =(const Polynome &);
		// Calcul:
		K operator ()(K x) const;
		K deriv(K x) const;
};

template <class K>
Polynome<K>::Polynome(const std::vector<K> & v): degree(v.size()-1), coeff(nullptr) {
	coeff= new K[v.size()];
	for (unsigned i = 0; i < v.size(); i++)
	{
		coeff[i]=v[i];
	}
}

template <class K>
Polynome<K>::Polynome(const Polynome<K> & P): degree(P.degree), coeff(nullptr) {
	coeff = new K[degree+1];
	for (int i = 0; i < degree+1; i++)
	{
		coeff[i]=P.coeff[i];
	}
}

template <class K>
Polynome<K> & Polynome<K>::operator =(const Polynome<K> & P) {
	if( this != &P) {
		if( degree != P.degree ) {
			delete [] coeff;
			degree=P.degree;
			coeff = new K[degree+1];
		}
		for (int i = 0; i < degree+1; i++)
		{
			coeff[i]=P.coeff[i];
		}
	}
	return *this;
}

template <class K> 
K Polynome<K>::operator ()(K x) const {
	K xpow=1.;
	K s=coeff[0];
	for (int i = 1; i < degree+1; i++)
	{
		xpow *= x;
		s += xpow*coeff[i];
	}
	return s;
}

template <class K>
K Polynome<K>::deriv(K x) const {
	K xpow=1.;
	K s=0.;
	for (int i = 1; i < degree+1; i++)
	{
		s += i*xpow*coeff[i];
		xpow *= x;
	}
	return s;
}
#endif

