#ifndef MY_CLASS_PERM
#define MY_CLASS_PERM
	#include <iostream>
	#include <vector>
	#include <random>
	#include <list>

class Permutation{
	// question 2.1 & 2.2
	private:
		int n;
		std::vector<int> images;
	
	// question 2.3
	public:
		// Constructeurs
		Permutation(int _n=1);		// identité de taille n0
		Permutation(const std::vector<int> &v);		// création par vecteur
		Permutation(int _n, std::mt19937 g);		// génération de taille n0 avec aléatoire g
		
		// Méthodes
		std::vector<int> fixed_points() const;
		// std::list<Cycle> cycles() const;
		int order() const;
		Permutation inverse();
		bool is_derangement() const;

		// Opérateurs
		friend std::ostream & operator<<(std::ostream &o, const Permutation &P);
		friend std::istream & operator>>(std::istream &i, Permutation &P);
		friend std::vector<int> operator*(const std::vector<int> &P1, const std::vector<int> &P2);
		// question 2.9
		int operator[](int i) const {	return images[i]; };

		// Accesseurs
		// question 2.8
		int size() const {	return n; };		
};
#endif
