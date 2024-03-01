/*

  Un programme qui lit le contenu d'un fichier planeur.dat et exécute les

  Ici, le contenu de planeur.dat est le suivant :
  8 8
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


int main(void)
{
	// On crée un quadrillage de taille 4x4
	jeu_vie J(4,4);

	// On affiche le nombre de voisins occupés de (0,0)
	std::cout << J.voisins(0,0) << std::endl;

	// On ouvre le fichier planeur.dat pour lire son
	// contenu (supposé correctement formaté)
	std::ifstream entree("planeur.dat");

	// On lit le contenu de planeur.dat, que l'on stocke dans J
	J = jeu_vie(entree);

	// On referme planeur.dat
	entree.close();

	// On affiche la configuration initiale
	std::cout << "État initial\n";
	J.affichage(std::cout);
	std::cout << "\n";

	// On affiche les 20 configurations suivantes
	for (int i=1; i<=20; i++){
		J.iteration(); // On itère
		std::cout << "Itération " << i << "\n";
		J.affichage(std::cout); // On affiche
		std::cout << "\n";
	}

	// On crée un générateur de nombres pseudo-aléatoires
	std::mt19937 gen(time(nullptr));
	
	jeu_vie J_random(15,25,0.3,gen);
	
	// On fait 100 itérations
	for (int i=0; i<100; i++)
		J_random.iteration();

	// On affiche la dernière configuration
	std::cout << "Itération " << 100 << "\n";
	J_random.affichage(std::cout);
	std::cout << "\n";

	// On parcourt tous les p de {0.1, 0.2, ..., 0.9}
	for (double p=0.1; p<0.95; p += 0.1){

		// N va compter le nombre de cellules
		int N = 0;
		
		// On fait 100 réalisations indépendantes
		for (int realisation = 0; realisation<100; realisation++){
			jeu_vie J_MC(15,25,p,gen);

			// On fait evoluer 100 fois
			for (int i=0; i<100; i++)
				J_MC.iteration();

			N += J_MC.nb_cellules();
		}
		std::cout << "p=" << p << " ; nombre moyen de cellules : "<< N * 1./100 << "\n";
	}

	return 0;
}

