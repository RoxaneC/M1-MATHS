#include "my_permutation.hpp"
#include <iostream>
#include <vector>

using namespace std;

// Constructeurs
// question 2.4
Permutation::Permutation(int _n): n(_n), images(_n){
	for(int i=0 ; i<_n ; i++){
		images[i] = i;
	}
}
// question 2.11
Permutation::Permutation(const vector<int> &v): n(v.size()), images(v) {
	// suffit ?
};

// Méthodes


// Opérateurs
// question 2.5
ostream & operator<<(ostream &o, const Permutation &P){
	o << P.n << " : ";
	for(int i=0 ; i<P.n ; i++) {
		o << P.images[i] << " ";
	}
	o << "\n";
	return o;
};

// question 2.7
istream & operator>>(std::istream &i, Permutation &P){
	//
	string aux;
	i >> P.n;
	for(int j=0 ; j<P.n ; j++){
		i >> P.images[j];
	}
	return i;
};

int main(){
	// question 2.6
	Permutation perm_test(6);
	cout << perm_test;

	return 0;
}
