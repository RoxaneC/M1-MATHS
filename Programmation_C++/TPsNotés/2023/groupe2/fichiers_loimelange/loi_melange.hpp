//NOM:
//PRENOM:
//# étudiant:

#ifndef LOI_MELANGE_HPP
#define LOI_MELANGE_HPP


// bibliothèques à compléter 
#include <vector>
#include <random>
#include <iostream>

// déclarations à compléter
template <class RV> class Melange;
template <class RV>
std::ostream & operator<<(std::ostream &o, const Melange<RV> &m);

template <class RV>
Melange<RV> operator+(const Melange<RV> &m1, const Melange<RV> &m2);

template <class RV>
class Melange {
	private:
		std::vector<RV> modes;
		std::discrete_distribution<int> choose_mode;
		
	public:
	  // Constructeurs
	  Melange(): modes(), choose_mode(){};
	  // question 12
	  Melange(const std::vector<typename RV::param_type> &v_param, const std::vector<double> &v_poids);

		// Accesseurs
		// question 2
		int nb_of_modes() const {	return modes.size(); };
		// question 3
		std::vector<double> weights() const {	return choose_mode.probabilities(); };
		// question 4
		RV operator[](int i) const {	return modes[i]; };
		
		// Ajout d'un mode
		// question 6
		void add_mode(const double alpha, const RV & to_add);
		
		// Réalisation
		// question 8
		template <typename RNG>
		typename RV::result_type operator()(RNG & G);
		
		// question 5
		void print_type() const {	std::cout << typeid( RV() ).name() << "\n "; };

		// question 11
		friend std::ostream & operator<< <>(std::ostream &o, const Melange<RV> &m);

		// question 14
		friend Melange<RV> operator+ <>(const Melange<RV> &m1, const Melange<RV> &m2);

};



// question 6
// PAS CLAIR
template <class RV>
void Melange<RV>::add_mode(double alpha, const RV & to_add){
	std::vector<double> new_alphas;

	if (modes.empty()) {
		new_alphas.push_back(1.);
	} else {
		new_alphas = choose_mode.probabilities();
		transform(	new_alphas.begin(), new_alphas.end(), new_alphas.begin(),
					[alpha](double p){	return p*(1-alpha); });
		new_alphas.push_back(alpha);
	}

	modes.push_back(to_add);
	choose_mode = std::discrete_distribution<int>(new_alphas.begin(), new_alphas.end());
	// ERREUR DE SEGMENTATION SI FAIT DIRECTEMENT SUR LE .probabilities() !?!
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
std::ostream & operator<<(std::ostream &o, const Melange<RV> &m){
	o << m.nb_of_modes() << "\n";

	for(int i=0 ; i<m.nb_of_modes() ; i++){
		o << m.weights()[i] << "\t" << m[i] << "\n";
	}
	return o;
}

// question 12
template <class RV>
Melange<RV>::Melange(const std::vector<typename RV::param_type> &v_params, const std::vector<double> &v_poids):
		modes(v_params.size()),
		choose_mode(v_poids.begin(), v_poids.end()) {
	//
	for(int i=0 ; i<v_params.size() ; i++){
		modes[i] = RV(v_params[i]);
	}
}

// question 14
template <class RV>
Melange<RV> operator+(const Melange<RV> &m1, const Melange<RV> &m2){
	std::vector<double> weights = m1.weights();
	std::vector<double> aux = m2.weights();
	weights.insert(weights.end(), aux.begin(), aux.end());
	transform(	weights.begin(), weights.end(), weights.begin(),
				[](double d){ return d*0.5; });

	
	std::vector<typename RV::param_type> params(m1.nb_of_modes() + m2.nb_of_modes());
	for(int i=0 ; i<m1.nb_of_modes() ; i++){
		params[i] = m1[i].param();
	}
	for(int i=0 ; i<m2.nb_of_modes() ; i++){
		params[i+m1.nb_of_modes()] = m2[i].param();
	}

	Melange<RV> res(params, weights);
	return res;
}


#endif
