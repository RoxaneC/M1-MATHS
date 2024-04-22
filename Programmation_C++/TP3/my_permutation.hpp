#ifndef MY_CLASS_PERM
#define MY_CLASS_PERM

#include <iostream>
#include <vector>
#include <random>
#include <list>

class Permutation;
class Cycle;

class Permutation{
	// question 3.1 & 3.2
	private:
		int n;
		std::vector<int> images;
	
	// question 3.3
	public:
		// Constructeurs
		Permutation(int _n=1);		// identité de taille n0
		Permutation(const std::vector<int> &v);		// création par vecteur
		Permutation(int _n, std::mt19937 &g);		// génération de taille n0 avec aléatoire g
		
		// Méthodes
		std::list<int> fixed_points() const;
		std::list<Cycle> cycles() const;
		long int order() const;
		Permutation inverse() const;
		bool is_derangement() const;

		// Opérateurs
		friend std::ostream & operator<<(std::ostream &o, const Permutation &P);
		friend std::istream & operator>>(std::istream &i, Permutation &P);
		friend Permutation operator*(const Permutation &P1, const Permutation &P2);
		// question 3.9
		int operator[](int i) const {	return images[i]; };
		// question 3.10 : pour ne pas casser l'objet Permutation

		// Accesseurs
		// question 3.8
		int size() const {	return n; };		
};

class Cycle {
	private:
		std::vector<int> elem;
		// question 3.17
		// sans verification : sans vérifier si le point est déjà dans le cycle (ce n'est plus un cycle)
		// privée : pour ne pas que l'utilisateur se serve de cette méthode (peut casser les bijections)
		void add_last_point(int pt) {	elem.push_back(pt); };	// ajoute un point à la fin du cycle
		std::vector<int>::iterator find(int i) const;

	public:
		// question 3.16 : pas besoin de constructeur car vector à déjà un constructeur

		// Accesseur
		// question 3.18
		long int order() const {	return elem.size();};

		// Méthodes
		int operator[](int i) const {	return elem[i]; };		// uses find
		Cycle inverse() const;

		// Opérateurs
		// question 3.19
		friend std::ostream & operator<<(std::ostream &o, const Cycle &C);
		friend bool operator<(const Cycle &C1, const Cycle &C2);

		// question 3.20
		friend class Permutation;

};

#endif
