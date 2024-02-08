#include <iostream>
#include <vector>
#include <list>

class Permutation{
	// question 2.1 & 2.2
	private:
		int n;
		std::vector<int> images;
	
	// question 2.3
	public:
		// Constructeurs
		Permutation(int n0=1);		// identité de taille n0
		Permutation(const std::vector<int> &v);		// création par vecteur
		Permutation(int n0, std::mt19937 g);		// génération de taille n0 avec aléatoire g
		
		// Méthodes
		std::vector<int> fixed_points() const;
		std::list<Cycle> cycles() const;
		int order() const;
		Permutation inverse();
		bool is_derangement() const;

		// Opérateurs
		friend ostream & operator<<(std::ostream &o, const Permutation &P);
		friend std::vector<int> operator*(const std::vector<int> &P, const std::vector<int> &P);
		
};
