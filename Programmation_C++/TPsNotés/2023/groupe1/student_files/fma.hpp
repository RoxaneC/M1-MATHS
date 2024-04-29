//NOM:
//PRENOM:
//# étudiant:
#ifndef FINITE_ATOMIC_MEASURES_HPP
#define FINITE_ATOMIC_MEASURES_HPP

// bibliothèques à compléter !!!
#include <map>
#include <iostream>
#include <numeric>
#include <cmath>

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
template <class E> Finite_atomic_measure<E> operator+(const Finite_atomic_measure<E> &fam1, const Finite_atomic_measure<E> &fam2);


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
        // BONUS : question 17
        // reférence constante pour ne pas que l'accesseur puisse modifier le champs renvoyé !
        const std::map<E, double> & atomic_masses() const {  return mass; };
        // BONUS : question 18
        friend Finite_atomic_measure<E> operator+<>(const Finite_atomic_measure<E> & fam1, const Finite_atomic_measure<E> & fam2);

        //method templates:
        template <class Domain > double measure(const Domain &) const; 
		template < class RealFunction_on_E > double integral(const RealFunction_on_E & f) const;
        
};

// question 3
template <class E>
double Finite_atomic_measure<E>::total_mass() const {
    double res = std::accumulate(    mass.begin(), mass.end(), 0.,
                                    [](double d, const pair<E, double> &p){   return d + p.second; } );

    return res;
}

// question 5
template <class E>
std::ostream & operator<<(std::ostream &o, const Finite_atomic_measure<E> &fam){
    o << fam.nb_of_atoms() << "\n";
    for(const std::pair<E, double> &p: fam.mass){
        o << p.first << "\t" << p.second << "\n";
    }

    return o;
}

// question 7
template <class E>
template <class Domain>
double Finite_atomic_measure<E>::measure(const Domain & D) const{
    double res = std::accumulate(    mass.begin(), mass.end(), 0.,
                                    [D](double d, const std::pair<E, double> &p){   return (D.contains(p.first)) ? d + p.second : d; } );
    return res;
}

// question 10
template <class E>
template <class RealFunction_on_E>
double Finite_atomic_measure<E>::integral(const RealFunction_on_E & f) const{
    double res = std::accumulate(    mass.begin(), mass.end(), 0.,
                                    [f](double d, const std::pair<E, double> &p){   return d + p.second*f(p.first); } );
    return res;
}

// question 11
template <class E>
std::istream & operator>>(std::istream &i, Finite_atomic_measure<E> &fam){
    fam.mass.clear();

    int n;
    i >> n;

    E x; double d;
    while(i >> x >> d){
        fam.mass[x] += d;
    }
    return i;
}

// question 13
template < class E1, class Function >  
Finite_atomic_measure<invoke_result_t< Function, E1> > image(const Finite_atomic_measure<E1> & mu, const Function & f){
    Finite_atomic_measure<invoke_result_t< Function, E1> > nu;
    for(const pair<E1, double> &p : mu.get_mass()){
        nu.add_mass(f(p.first), p.second);
    }
    return nu;
}

// BONUS : question 18
template <class E>
Finite_atomic_measure<E> operator+(const Finite_atomic_measure<E> & fam1, const Finite_atomic_measure<E> & fam2){
    Finite_atomic_measure<E> res = fam1;
    for(const pair<E, double> &p : fam2.mass){
        res.add_mass(p.first, p.second);
    }

    return res;
}


#endif
