//NOM: CELLIER
//PRENOM: Roxane

//----- COMPLETER SI NECESSAIRE
#include "piecewisefunction.hpp"

#include <set>
#include <fstream>


PiecewiseFn<std::set<int>,Affine_Fn<double>> make_int_fn_from_file( std::istream & is, double default_value) {
    //COMPLETER
    // question 10
    PiecewiseFn<std::set<int>,Affine_Fn<double>> PWFn(default_value);
    int nb_segment;
    is >> nb_segment;
    
    for(int i=0 ; i<nb_segment ; i++){
		std::set<int> S_i;
		
		int taille;	double value;
		is >> taille >> value;
		
		for(int j=0 ; j<taille ;j++){
			int x;
			is >> x;
			S_i.insert(x);
		}
		PWFn.add_piece(S_i, Affine_Fn<double>(0., value));
	}
	
	return PWFn;
}


int main()  {
	// vérification question 11 (-std='c++20')
    auto input = std::ifstream("data2.txt");
    auto f = make_int_fn_from_file(input,0.5);
    for (int i = 0; i < 20; i++)
    {
        std::cout << i << ":\t" << f(i) << "\n";
    }
    
    return 0;
}
