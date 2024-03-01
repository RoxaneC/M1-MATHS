/*

  Un programme qui lit le contenu d'un fichier planeur.dat et exécute les

  Ici, le contenu de planeur.dat est le suivant :

  ..X.....
  X.X.....
  .XX.....
  ........
  ........
  ........
  ........
  ........
  
  ce qui correspond à un "planeur", c'est-à-dire une configuration de cellules
  qui se déplace en gardant la même forme (pour être précis, elle se déplace
  d'une case vers le bas à droite toutes les 4 itérations 

 */



#include "jeu_vie.hpp"
#include <fstream> // Pour lire/écrire dans un fichier

int main()
{
  // On crée un quadrillage de taille 8x8
  jeu_vie J(8,8);
  
  // On ouvre le fichier planeur.dat pour lire son
  // contenu (supposé correctement formaté)
  std::ifstream entree("planeur.dat");

  // On lit le contenu de planeur.dat, que l'on stocke dans J
  J.lecture(entree);

  // On referme planeur.dat
  entree.close();

  // On affiche la configuration initiale
  std::cout << "État initial\n";
  J.affichage(std::cout);
  std::cout << "\n";

  // On affiche les 20 configurations suivantes
  for (int i=1; i<=20; i++)
	{
	  J.iteration(); // On itère
	  std::cout << "Itération " << i << "\n";
	  J.affichage(std::cout); // On affiche
	  std::cout << "\n";
	}
  
  return 0;
}
