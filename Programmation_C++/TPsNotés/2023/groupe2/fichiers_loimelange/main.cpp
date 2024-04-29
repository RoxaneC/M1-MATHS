//NOM:
//PRENOM:
//# étudiant:

// à compléter
#include "loi_melange.hpp"
#include <typeinfo>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <random>

using namespace std;

int main() {

  	// Creation d'un mélange vide
	// question 5
	// Melange< bernoulli_distribution<int> > M_bernoulli;
	// ERREUR : faire un template d'un template de class
	Melange< bernoulli_distribution > M_bernoulli;	
	M_bernoulli.print_type();
	
	// question 7
	bernoulli_distribution B1(0.5);
	bernoulli_distribution B2(0.2);
	M_bernoulli.add_mode(1., B1);
	M_bernoulli.add_mode(0.3, B2);

	// question 9
	mt19937 Gen(time(nullptr));
	cout << "Réalisation du mélange : " << M_bernoulli(Gen) << "\n";

	// question 10
	int nb_real = 100000;
	double moy_theo = 0.5*M_bernoulli.weights()[0] + 0.2*M_bernoulli.weights()[1];
	cout << "Moyenne théorique : " << moy_theo << "\n";
	double moy_emp = 0.;
	for(int i=0 ; i<nb_real ; i++){
		moy_emp += M_bernoulli(Gen);
	}
	cout << "Moyenne empirique : " << moy_emp/nb_real << "\n";

	// question 11 test
	cout << M_bernoulli << "\n";

	// question 13
	ifstream file("melange_gauss_1.txt");
	int n;
	file >> n;
	vector<double> v_poids(n);	double d; 
	vector<typename normal_distribution<double>::param_type> v_params(n);
	double m;	double dev_std;
	for(int i=0 ; i<n ; i++){
		file >> d >> m >> dev_std;
		v_poids[i] = d;
		v_params[i] = typename normal_distribution<double>::param_type (m, dev_std);
	}
	file.close();
	Melange<normal_distribution<double>> M_gaussian_1(v_params, v_poids);
	cout << "Premier mode du mélange gaussien 1 : " << M_gaussian_1[0] << "\n\n";

	// question 15
	ifstream file2("melange_gauss_2.txt");
	file2 >> n;
	vector<double> v_poids2(n);
	vector<typename normal_distribution<double>::param_type> v_params2(n);
	for(int i=0 ; i<n ; i++){
		file2 >> d >> m >> dev_std;
		v_poids2[i] = d;
		v_params2[i] = typename normal_distribution<double>::param_type (m, dev_std);
	}
	file2.close();
	Melange<normal_distribution<double>> M_gaussian_2(v_params2, v_poids2);

	// question 16
	cout << "Somme des mélange des deux gaussiennes :" << M_gaussian_1+M_gaussian_2 << "\n";


	return 0;
}

