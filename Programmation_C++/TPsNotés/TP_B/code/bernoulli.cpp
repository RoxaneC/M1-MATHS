/*

  Un programme qui simule 100 itérations du jeu de la vie partant
  d'une configuration aléatoire tirée suivant des lois de Bernoulli.

 */


#include "jeu_vie.hpp"
#include <random> // Pour l'aléatoire (il faut donc compiler avec l'option -std=c++11)

// Les paramètres du modèle
const double p = 0.3; // Probabilité de placer une cellule en chaque point
const int L = 25; // Largeur
const int H = 15; // Hauteur



int main(void)
{
  jeu_vie J(H,L);


  // On initialise le générateur de nombres pseudo-aléatoires.
  // R sert à initialiser avec une valeur différente à chaque
  // exécution du programme
  std::random_device R;
  std::mt19937 gen(R());

  // Une variable de loi de Bernoulli de paramètre p
  std::bernoulli_distribution X(p);
  

  // On place des cellules selon la loi de Bernoulli
  for (int i=0; i<H; i++)
	for (int j=0; j<L; j++)
	  J.modif(i,j,X(gen));

  // On affiche l'état initial
  std::cout << "État initial\n";
  J.affichage(std::cout);
  std::cout << "\n";
  

  // On fait 100 itérations, en affichant à chaque fois la configuration
  for (int i=1; i<=100; i++)
	{
	  J.iteration();
	  std::cout << "Itération " << i << "\n";
	  J.affichage(std::cout);
	  std::cout << "\n";
	}
  
  return 0;
}
