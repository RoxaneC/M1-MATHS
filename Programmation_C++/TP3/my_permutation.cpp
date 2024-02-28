#include "my_permutation.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <list>

using namespace std;

// Constructeurs
// question 2.4
Permutation::Permutation(int _n): n(_n), images(_n){
	for(int i=0 ; i<_n ; i++){
		images[i] = i;
	}
}
// question 2.11
Permutation::Permutation(const vector<int> &v): n(v.size()), images(v) {};


// Méthodes
// question 2.14
list<int> Permutation::fixed_points() const {
	//
	list<int> list_pt_fix;
	for(int i=0 ; i<n ; i++){
		if (images[i]==i)	list_pt_fix.push_back(i);
	}
	return list_pt_fix;
};

bool Permutation::is_derangement() const {	return !(fixed_points().empty());};




// Opérateurs
// question 2.5
ostream & operator<<(ostream &o, const Permutation &P){
	o << P.n << " : ";
	for(int k : P.images) {
		o << k << " ";
	}
	o << "\n";
	return o;
};

// question 2.7
istream & operator>>(std::istream &i, Permutation &P){
	char aux;		// passer après les ':'
	i >> P.n >> aux;
	P.images.resize(P.n);
	for(int & k : P.images){
		i >> k;
	}
	return i;
};

// question 2.13
Permutation operator*(const Permutation &P1, const Permutation &P2){
	int taille1 = P1.n;
	int taille2 = P2.n;

	if (taille1 == taille2){	// si vecteur de la même taille
		Permutation perm_res(taille1);

		for(int i=0 ; i<taille1 ; i++){
			perm_res.images[i] = P1[ P2[i] ];
		}
		return perm_res;

	} else if (taille1 < taille2) {
		Permutation perm_res(taille2);

		for(int i=0 ; i<taille2 ; i++){
			if (i<taille1){
				perm_res.images[i] = P1[ P2[i] ];
			} else {
				perm_res.images[i] = P2[i];
			}
		}
		return perm_res;

	} else {
		Permutation perm_res(taille1);

		for(int i=0 ; i<taille1 ; i++){
			if (i<taille2){
				perm_res.images[i] = P2[ P1[i] ];
			} else {
				perm_res.images[i] = P1[i];
			}
		}
		return perm_res;

	}
}




int main(){
	// question 2.6
	Permutation perm_test_out(6);
	cout << "a >> " << perm_test_out << "\n";
	cout << perm_test_out[4] << "\n";		// question 2.10 : ?
	
	// question 2.7
	Permutation perm_test_in;
	ifstream f_in("file_s.dat");
	f_in >> perm_test_in;
	f_in.close();
	
	ofstream f_out("test_file_s.dat");
	f_out << perm_test_in;
	f_out.close();
	
	// question 2.11
	// vector<int> v{2,4,5,3,1,0};
	vector<int> v{2,4,3,1,0};
	Permutation perm_test_vect(v);
	cout << "b >> " << perm_test_vect << "\n";
	
	// question 2.12 : pourquoi pas ?
	
	// test question 2.13
	/* for(int i=0; i<=6; ++i) {
		std::cout << "a^" << i << "\nb >> " << perm_test_vect << "\n";
		perm_test_vect = perm_test_vect*perm_test_out;
	} */
	for(int i=0; i<=6; ++i) {
		std::cout << "b^" << i << "\na >> " << perm_test_out << "\n";
		perm_test_out = perm_test_out*perm_test_vect;
	}

	// test question 2.14
	/* list<int> fp = a.fixed_points();
	copy( fp.begin(), fp.end(), ostream_iterator<int>(std::cout," ") );
	cout << "\n"; */

	return 0;
}
