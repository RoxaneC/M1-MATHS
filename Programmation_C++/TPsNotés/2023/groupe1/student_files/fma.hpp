//NOM:
//PRENOM:
//# étudiant:
#ifndef FINITE_ATOMIC_MEASURES_HPP
#define FINITE_ATOMIC_MEASURES_HPP

// bibliothèques à compléter !!!

//quelques déclarations

template < class E > 
    class Finite_atomic_measure;

template < class E1, class Function >  
    Finite_atomic_measure< std::invoke_result_t< Function, E1> > image(const Finite_atomic_measure<E1> & mu, const Function & f);

template <class E>
	Finite_atomic_measure<E> image(const Finite_atomic_measure<E> & mu1, const Finite_atomic_measure<E> & mu2);

//définition de la classe: 

template < class E >
class Finite_atomic_measure {
	private:
        std::map< E, double > mass;//atomes et leurs masses associées
    public:
        ... constructeur par défaut...
        
        ... nb_of_atoms() ...
        ... total_mass() ...
		... add_mass(const E & point, double mass_value) ...
        
        //method templates:
        template <class Domain > double measure(const Domain &) const; 
		template < class RealFunction_on_E > double integral(const RealFunction_on_E & f) const;
        
};
#endif
