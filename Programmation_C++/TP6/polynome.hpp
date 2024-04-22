#ifndef MY_POLY
#define MY_POLY

#include <vector>
#include <cmath>
#include <limits>
#include <ostream>
#include <algorithm>
#include <iterator>
#include <string>

template <class T> class Polynome;
template <class T> std::ostream & operator<<(std::ostream &o, const Polynome<T> &P);
template <class T> Polynome<T> operator+(const Polynome<T> &P1, const Polynome<T> &P2);
template <class T> Polynome<T> operator-(const Polynome<T> &P1, const Polynome<T> &P2);

// question 6.1
template <typename T>
bool is_zero(T a){
	return a==0;
};
template <typename T>
bool is_one(T a){
	return a==1;
};

// question 6.2
template <>
bool is_zero(double a){
	return std::abs(a)<=1e-15;
};
template <>
bool is_one(double a){
	return std::abs(a-1.)<=1e-15;
};

// question 6.3
/* bool is_zero(std::complex<T> a){
	return std::abs(a.real())<=1e-15;
};
bool is_one(double a){
	return std::abs(a-1)<=1e-15;
}; */


// question 6.4
template <class T>
class Polynome {
	private:
		int n;
		std::vector<T> coeff;
		// question 6.13
		Polynome<T> extend(int m) const;
		// question 6.14
		void adjust();
		
	public:
		// question 6.5
		Polynome(): n(-std::numeric_limits<int>::infinity()), coeff() {};		// polynome nul
		Polynome(T a, int m);		// monome
		Polynome(const std::vector<T> &vect): coeff(vect), n(vect.size()-1) {};		// polynome par vecteur
		// question 6.6
		int degre() const {	return n; };
		// question 6.7
		T operator[](int i) const {	return (i <= n+1) ? coeff[i] : 0; };
		// question 6.11
		friend std::ostream & operator<< <>(std::ostream &o, const Polynome<T> &P);
		// question 6.15
		friend Polynome<T> operator+ <>(const Polynome<T> &P1, const Polynome<T> &P2);
		friend Polynome<T> operator- <>(const Polynome<T> &P1, const Polynome<T> &P2);
};

// coder dans le cpp plutôt !
// question 6.5
template <class T>
Polynome<T>::Polynome(T a, int m): n(m), coeff(m+1, 0){
	coeff[m+1] = a;
};

// question 6.8
template <typename T>
void affiche_monome(std::ostream &s, const T &a, int n) {
	if (!is_zero(a) && n>=0) {
		switch(n){
			case 0:	s << a;
					break;
			case 1:	s << a << "x";
					break;
			default:	s << a << "*x^" << n;
		}
	}
};

// question 6.10
template <class T>
std::ostream & operator<<(std::ostream &o, const Polynome<T> &P){
	for(int i=0 ; i<P.degre() ; i++){
		affiche_monome(o, P[i], i);
		o << " + ";
	}
	affiche_monome(o, P[P.degre()], P.degre());
	return o;
};

// question 6.13
template <class T>
Polynome<T> Polynome<T>::extend(int m) const{
	if (m>n){
		std::vector<T> new_coeff(coeff);
		new_coeff.resize(m+1, 0);
		Polynome<T> P(new_coeff);
		return P;
	} else {
		return *this;
	}
};

// question 6.14
template <class T>
void Polynome<T>::adjust(){
	int ind = std::distance(std::find_if(coeff.rbegin(), coeff.rend(), [](T a){ return !is_zero(a);}), coeff.rend());
	coeff.resize(ind);
	n = ind-1;
};

// question 6.15
template <typename T>
Polynome<T> operator+(const Polynome<T> &P1, const Polynome<T> &P2){
	if (P1.n > P2.n){
		Polynome<T> new_P = P2.extend(P1.n);
		std::transform(	new_P.coeff.begin(), new_P.coeff.end(), P1.coeff.begin(), new_P.coeff.begin(),
						[](const T &a1, const T &a2){ return a2+a1; });
		new_P.adjust();
		return new_P;
	} else {
		Polynome<T> new_P = P1.extend(P2.n);
		std::transform(	new_P.coeff.begin(), new_P.coeff.end(), P2.coeff.begin(), new_P.coeff.begin(),
						[](const T &a1, const T &a2){ return a1+a2; });
		new_P.adjust();
		return new_P;
	}
};
template <typename T>
Polynome<T> operator-(const Polynome<T> &P1, const Polynome<T> &P2){
	if (P1.n > P2.n){
		Polynome<T> new_P = P2.extend(P1.n);
		std::transform(	new_P.coeff.begin(), new_P.coeff.end(), P1.coeff.begin(), new_P.coeff.begin(),
						[](const T &a1, const T &a2){ return a2-a1; });
		new_P.adjust();
		return new_P;
	} else {
		Polynome<T> new_P = P1.extend(P2.n);
		std::transform(	new_P.coeff.begin(), new_P.coeff.end(), P2.coeff.begin(), new_P.coeff.begin(),
						[](const T &a1, const T &a2){ return a1-a2; });
		new_P.adjust();
		return new_P;
	}
};

#endif


// POUR DU DEBUG :
// std::cout << .... << "\n";		/!\ memoire tampon ie n'affiche pas immediatement l'information
// ---> std::cout << .... << std::endl();
// OU ---> std::flush();


// RELATION D'AMITIÉ avec classes (1) :
// ---> template <typename T>
// ---> Polynome {
// ---> blabla
// ---> friend (+) template avec T remplacé par une autre variable muette
// ---> };
// en particulier amitié pour tous les types possible (question 6.10)
// --> ex : template <typename U> friend std::ostream & operator<<(std::ostream &o, const Polynome<U> &P);

// RELATION D'AMITIÉ avec classes (2) :
// ---> template <class T> Polynome;
// ---> template <class T>
// ---> Polynome {
// ---> blabla
// ---> friend (+) T dans déclaration
// ---> };
// ---> et ajouter les chevrons dans déclaration dans la classe /!\ operator_ <> /!\ PAR COEUR
// amitié uniquement pour son propre type T (question 6.11)
// --> ex : friend std::ostream & operator<< <>(std::ostream &o, const Polynome<T> &P);


// (T) x ---> opérateur de conversion
// T(x) ---> constructeur
