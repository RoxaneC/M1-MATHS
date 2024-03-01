#ifndef _JEU_VIE_HPP_
#define _JEU_VIE_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <random>


class jeu_vie{
	private:
		int H, L; // Les dimensions de la grille

		// Les positions des cellules : config[i][j] vaut true si une
		// particule est présente en ième ligne et jème colonne.
		std::vector<std::vector<bool> > config; 


	public:
		// Un constructeur créant une grille vide de taille HxL
		jeu_vie(int _H, int _L);
		jeu_vie(std::istream &flux);
		jeu_vie(int _H, int _L, double p, std::mt19937& G);


		// Des accesseurs pour les variables H et L
		int hauteur() const {	return H; }
		int largeur() const {	return L; }

		// Le calcul du nombre de voisins
		int voisins(int i, int j) const;

		// Une itération du jeu de la vie
		void iteration();

		// Méthode pour écrire une configuration vers un flux
		void affichage(std::ostream &flux) const;

		// Le calcul du nombre de cellules présentes sur la grille
		int nb_cellules() const;
};

#endif
