#include "my_permutation.hpp"

using namespace std;

// Constructeurs
Permutation::Permutation(int n0): n(n0), images(n0){
	fiota(images.begin(), images.end(), 0);
};

// Méthodes


// Opérateurs
Permutation::operator <<()
