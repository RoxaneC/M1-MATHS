//NOM: CELLIER
//PRENOM: Roxane

// COMPLETER SI NECESSAIRE
#include "linearform.hpp"
#include "piecewisefunction.hpp"

#include <fstream>

// specialisation de test_if_contains ici
template <>
bool test_if_contains(const std::vector<Segment> & D, const std::vector<double> & v) {
    // question 13
    bool test=true;
    for(int i=0 ; i<D.size() ; i++){
		if (!D[i].contains(v[i]))	test=false;
	}
    
    return test;
}

int main() {
    //compléter
    // question 14 (fonctionne pas, classe pas codée)
    /*int dim = 3;
    std::ifstream file("data3.txt");
    LinearForm<double, 3> LF();
    file >> LF; */
}

