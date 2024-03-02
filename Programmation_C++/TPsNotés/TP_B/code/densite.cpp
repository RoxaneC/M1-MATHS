/*

  Un programme qui calcule (par méthode de Monte Carlo) la densité
  moyenne de cellules sur une grille 15x25 après 100 itérations du
  jeu de la vie, en fonction de la densité initiale.

  On trouve approximativement les résultats suivants :
  p=0.1 ; nombre moyen de cellules : 9
  p=0.2 ; nombre moyen de cellules : 21
  p=0.3 ; nombre moyen de cellules : 23
  p=0.4 ; nombre moyen de cellules : 23
  p=0.5 ; nombre moyen de cellules : 23
  p=0.6 ; nombre moyen de cellules : 21
  p=0.7 ; nombre moyen de cellules : 13
  p=0.8 ; nombre moyen de cellules : 4
  p=0.9 ; nombre moyen de cellules : 0.5

  La densité de cellule est à peu près la même pour p entre 0.2 et 0.6,
  mais elle chute beaucoup si il y a initialement trop ou pas assez
  de cellules.
  
 */


#include "jeu_vie.hpp"
#include <random> // Pour l'aléatoire (il faut donc compiler avec l'option -std=c++11)

// Les paramètres du modèle
const int L = 25; // Largeur
const int H = 15; // Hauteur

// Le nombre de réalisations indépendantes dans la calcul de Monte Carlo
const int nb_realis = 100;

// Le nombre d'itérations du jeu de la vie
const int nb_iter = 100;



int main(void)
{
  jeu_vie J(H,L);

  // On initialise le générateur, avec une graine quelconque
  std::mt19937 gen(1235);

  // On parcourt tous les p de {0.1, 0.2, ..., 0.9}
  for (double p=0.1; p<0.95; p += 0.1)
	{

	  // On définit une variable de Bernoulli de paramètre p
	  std::bernoulli_distribution X(p);

	  // N va compter le nombre de cellules
	  int N = 0;
	  // On fait nb_realis réalisations idépendante
	  for (int realisation = 0; realisation<nb_realis; realisation++)
		{
		  for (int i=0; i<H; i++)
			for (int j=0; j<L; j++)
			  J.modif(i,j,X(gen));
		  
		  
		  for (int i=1; i<=nb_iter; i++)
			  J.iteration();
		  N += J.nb_cellules();
		}
	  std::cout << "p=" << p << " ; nombre moyen de cellules : "<< N * 1./nb_iter << "\n";
	  
	}
	  
  return 0;
}
