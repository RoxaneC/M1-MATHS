//NOM:
//PRENOM:
//# étudiant:

#ifndef LOI_MELANGE_HPP
#define LOI_MELANGE_HPP


// bibliothèques à compléter 

// déclarations à compléter



template <class RV>
class Melange {
	private:
		std::vector<RV> modes;
		std::discrete_distribution<int> choose_mode; 
		
	public:
	  // Constructeurs
		 ... constructeur par défaut... 
		
		// Accesseurs
		... nb_of_modes() ...
		... weights() ...
		... operator[](...) ...
		
		// Ajout d'un mode
		... add_mode(... alpha, ... to_add) ...
		
		// Réalisation
		...
		typename RV::result_type operator()(...)...
		
		// ...

};


#endif
