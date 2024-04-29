//NOM:
//PRENOM:
//# étudiant:

// à compléter
#include "loi_melange.hpp"
#include <typeinfo>
#include <algorithm>
#include <cmath>
#include <fstream>

using namespace std;

// question 6
// PAS CLAIR
template <class RV>
void Melange<RV>::add_mode(double alpha, const RV & to_add){
	vector<double> new_alphas;

	if (modes.empty()) {
		new_alphas.push_back(1.);
	} else {
		new_alphas = choose_mode.probabilities();
		transform(	new_alphas.begin(), new_alphas.end(), new_alphas.begin(),
					[alpha](double p){	return p*(1-alpha); });
		new_alphas.push_back(alpha);
	}

	modes.push_back(to_add);
	choose_mode = discrete_distribution<int>(new_alphas.begin(), new_alphas.end());
	// ERREUR DE SEGMENTATION SI FAIT DIRECTEMENT SUR LE .probabilities() !!!
}

// question 8
template <class RV>
template <typename RNG>
typename RV::result_type Melange<RV>::operator()(RNG & G){
	int ind_mode = choose_mode(G);
	typename RV::result_type real = modes[ind_mode](G);
	return real;
}

// question 11
template <class RV>
ostream & operator<<(ostream &o, const Melange<RV> &m){
	o << m.nb_of_modes() << "\n";

	for(int i=0 ; i<m.nb_of_modes() ; i++){
		o << m.weights()[i] << "\t" << m[i] << "\n";
	}
	return o;
}

// question 12
template <class RV>
Melange<RV>::Melange(const vector<typename RV::param_type> &v_params, const vector<double> &v_poids): modes(v_params.size()), choose_mode(v_poids.begin(), v_poids.end()){
	for(int i=0 ; i<v_params.size() ; i++){
		modes[i] = RV(v_params[i]);
	}
}

// question 14
template <class RV>
Melange<RV> operator+(const Melange<RV> &m1, const Melange<RV> &m2){
	vector<double> weights = m1.weights();
	vector<double> aux = m2.weights();
	weights.insert(weights.end(), aux.begin(), aux.end());
	transform(	weights.begin(), weights.end(), weights.begin(),
				[](double d){ return d*0.5; });

	
	vector<typename RV::param_type> params(m1.nb_of_modes() + m2.nb_of_modes());
	for(int i=0 ; i<m1.nb_of_modes() ; i++){
		params[i] = m1[i].param();
	}
	for(int i=0 ; i<m2.nb_of_modes() ; i++){
		params[i+m1.nb_of_modes()] = m2[i].param();
	}

	Melange<RV> res(params, weights);
	return res;
}


int main() {

  	// Creation d'un mélange vide
	// question 5
	// Melange< bernoulli_distribution<int> > M_bernoulli;	ERREUR : faire un template d'un template de class ???
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

