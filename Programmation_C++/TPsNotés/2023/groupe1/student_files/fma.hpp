//NOM:
//PRENOM:
//# étudiant:
#ifndef FINITE_ATOMIC_MEASURES_HPP
#define FINITE_ATOMIC_MEASURES_HPP

// bibliothèques à compléter !!!
#include <map>
#include <iostream>

//quelques déclarations

template < class E > 
    class Finite_atomic_measure;

template < class E1, class Function >  
    Finite_atomic_measure< std::invoke_result_t< Function, E1> > image(const Finite_atomic_measure<E1> & mu, const Function & f);

template <class E>
	Finite_atomic_measure<E> image(const Finite_atomic_measure<E> & mu1, const Finite_atomic_measure<E> & mu2);


// question 5
template <class E> std::ostream & operator<<(std::ostream &o, const Finite_atomic_measure<E> &fam);
// question 11
template <class E> std::istream & operator>>(std::istream &o, Finite_atomic_measure<E> &fam);
// BONUS : question 18
template <class E> Finite_atomic_measure<E> operator+<>(const Finite_atomic_measure<E> &fam1, const Finite_atomic_measure<E> &fam2);


//définition de la classe:
// question 1
template < class E >
class Finite_atomic_measure {
	private:
        std::map< E, double > mass;//atomes et leurs masses associées
    public:
        Finite_atomic_measure(): mass() {};
        
        // question 2
        int nb_of_atoms() const {   return mass.size(); };
        double total_mass() const;
        // question 4
		void add_mass(const E & point, double mass_value){  mass[point] += mass_value; };
        // question 5
        friend std::ostream & operator<< <>(std::ostream &o, const Finite_atomic_measure<E> &fam);
        // question 11
        friend std::istream & operator>> <>(std::istream &i, Finite_atomic_measure<E> &fam);
        // question 13
        std::map<E, double> get_mass() const {  return mass; };

        // BONUS : question 16
        // ...
        // BONUS : question 17 (???)
        std::map<E, double> & atomic_masses() const {  return mass; };
        // BONUS : question 18
        friend Finite_atomic_measure<E> operator+<>(const Finite_atomic_measure<E> & fam1, const Finite_atomic_measure<E> & fam2);

        //method templates:
        template <class Domain > double measure(const Domain &) const; 
		template < class RealFunction_on_E > double integral(const RealFunction_on_E & f) const;
        
};
#endif
