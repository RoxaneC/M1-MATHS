#ifndef MY_POLY
#define MY_POLY

#include <vector>
#include <cmath>
#include <limits>
#include <ostream>

template <class T> class Polynome;
template <class T> std::ostream & operator<<(std::ostream &o, const Polynome<T> &P);


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
	return std::abs(a)<=1e-15;
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
		
	public:
		// question 6.5
		Polynome(): n(-1), coeff({-std::numeric_limits<T>::infinity()}) {};		// polynome nul
		Polynome(T a, int m);		// monome
		Polynome(std::vector<T> vect): coeff(vect), n(vect.size()-1) {};		// polynome par vecteur
		// question 6.6
		int degre() const {	return n; };
		// question 6.7
		T operator[](int i) const {	return (i <= n+1) ? coeff[i] : std::numeric_limits<T>::quiet_NaN(); };
		// question 6.10
		friend std::ostream & operator<< <>(std::ostream &o, const Polynome<T> &P);
};

// question 6.5
template <class T>
Polynome<T>::Polynome(T a, int m): n(m), coeff(m+1){
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
			default:	s << a << "x*^" << n;
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



#endif



// POUR DU DEBUG :
// std::cout << .... << "\n";		/!\ tampon ie n'affiche pas immediatement l'information
// ---> std::cout << .... << std::endl();
// ---> std::flush();


// RELATION D'AMITIÉ avec classes (1) :
// ---> template <typename T>
// ---> Polynome<T>
// ---> blabla
// ---> friend (+) template avec T remplacé par une autre variable muette
// en particulier amitié pour tous les types possible (question 6.10)

// RELATION D'AMITIÉ avec classes (2) :
// ---> template <class T> Polynome;
// ---> Polynome<T>
// ---> blabla
// ---> friend (+) T dans déclaration
// ---> et ajouter les chevrons dans déclaration dans la classe /!\ operator_ <> /!\ PAR COEUR
// amitié uniquement pour son propre type T (question 6.11)



