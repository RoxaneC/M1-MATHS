#include "my_permutation.hpp"
#include <iostream>
#include <vector>
#include <fstream>

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
//

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
	Permutation perm_res;
	int taille1 = P1.n;
	int taille2 = P2.n;
	
	if (taille1 == taille2){
		perm_res.images.resize(taille2);
		for(int i=0 ; i<taille1 ; i++){
			perm_res.images[i] = P1[ P2[i] ];
		}
	} else if (taille1 < taille2) {
		//
		Permutation small_res(taille1);
		small_res = P1*P2;
	}
	
	return perm_res;
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
	vector<int> v{2,4,5,3,1,0};
	Permutation perm_test_vect(v);
	cout << "b >> " << perm_test_vect << "\n";
	
	// question 2.12 : pourquoi pas ?
	
	// test question 2.13
	for(int i=0; i<=6; ++i) {
		std::cout << "a^" << i << "\nb >> " << perm_test_vect << "\n";
		perm_test_vect = perm_test_vect*perm_test_out;
	}

	return 0;
}
