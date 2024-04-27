#include "polynome.hpp"
#include <iostream>

using namespace std;

int main(){
	//Première partie
	Polynome<double> q;
	std::cout << "Degre de q : " << q.degre() << endl;

	vector<int> v1{6, 3, 0, 1, 5};
	Polynome<int> p1(v1);
	vector<int> v2{1,0,1};
	Polynome<int> p2(v2);
	
	/* std::complex<double> a (2.0,1.0);
	std::complex<double> b (0.0,1.0);
	vector<std::complex<double>> vc{a,b};

	Polynome<std::complex<double>> pc(vc);

	std::complex<int> one = 1;
	std::cout << "Is one one : " << is_one(one) << endl;
	std::cout << is_zero(a) << endl;
	affiche_monome(std::cout, a, 3);
	std::cout << std::endl; */
	std::cout << "p1 : " << p1 << std::endl;
	std::cout << "p2 : " << p2 << std::endl;
	
	
	//Deuxième partie
	// Somme, différénce, produit
	Polynome<int> sum = p1+p2;
	Polynome<int> diff = p1-p2;
	Polynome<int> prod = p1*p2;
	std::cout << "Somme : " << sum << std::endl;
	std::cout << "Différence : " << diff << std::endl;
	std::cout << "Produit : " << prod << std::endl;

// TEST
	double c=5;
	auto f1 = [c](int n){ return n+c; };
	auto f2 = [i=3](int n){ return n+i; };
	cout << f1(5) << "\n";
	cout << f2(5) << "\n";
// FIN TEST

	// Division et reste
	/*Polynome<int> div = p1/p2;
	Polynome<int> reste = p1%p2;
	std::cout << "Quotient : " << div << std::endl;
	std::cout << "Reste : " << reste << std::endl;

	// Evaluation en un point
	std::cout << "p1(2) : " << p1(2) << std::endl; */
	return 0;
}




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


// question 6.9
// std::is_same<T, std::complex<double>>::value
// ---> retourne un boolean : vérifie si les deux sont de même type
// Mais si compilation avec des int ? problème avec a.real(), a.image()
// ---> purger les branches inutiles au moment de la compilation
// ---> regarde la valeur dès la compilation :
// if constexpr(std::is_same<T, std::complex<double>>::value)
// ---> cependant réserve des cases mémoires, pas forcément opti ?