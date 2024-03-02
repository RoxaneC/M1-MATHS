#include "jeu_vie.hpp"

jeu_vie::jeu_vie(int _H, int _L) : H(_H), L(_L), config(H)  {
	// Pour l'instant, config est un vecteur de std::vector<bool> de taille H,
	// tel que chaque config[i] est un vecteur de bool de taille 0. On doit
	// donc redimensionner les config[i].
	for (int i=0; i<H; i++){
		config[i].resize(L);
		for (int j=0; j<L; j++)
			config[i][j] = false;
	}
}


jeu_vie::jeu_vie(std::istream &flux){
	// On lit la hauteur et la largeur et on prépare les vecteurs à remplir
	flux >> H;
	flux >> L;

	config.resize(H);

	std::string S;
	for (int i=0; i<H; i++){
		// On lit une ligne
		flux >> S;

		// On attribue la bonne taille 
		config[i].resize(L);

		// On parcourt les caractères de la ligne
		for (int j=0; j<L; j++){
			if (S[j] == 'X')
				config[i][j] = true;
			else
				config[i][j] = false;
		}
	}
}


jeu_vie::jeu_vie(int _H, int _L, double p, std::mt19937& G): jeu_vie(_H,_L){
	// On crée une Bernoulli de parametre p
	std::bernoulli_distribution X(p);

	// On remplit les cases
	for (int i=0; i<H; i++){
		for (int j=0; j<L; j++)
			config[i][j] = X(G);
		}
}


int jeu_vie::voisins(int i, int j) const{
	int nb_voisins=0;

	// Les voisins de config[i][j] ont des coordonnées valant
	// (i-1, i ou i+1) et (j-1,j ou j+1)
	for (int h=i-1; h<=i+1; h++)
		for (int l=j-1; l<=j+1; l++)
			// On exclut le point i,j lui-même, ainsi que les points hors-grille
			if (h>=0 and h<H and l>=0 and l<L and not (h==i and l==j) )
				nb_voisins += config[h][l];

	return nb_voisins;
}


void jeu_vie::iteration(void){
	// On crée une nouvelle configuration, qui va nous
	// servir à calculer la configuration à l'instant suivant.
	std::vector<std::vector<bool> > config_new = config;

	for (int i=0; i<H; i++){
		for (int j=0; j<L; j++){
			// On modifie config_new[i][j] en fonction des règles du jeu de la vie
			int n = voisins(i,j);

			// Si trop ou pas assez de voisins, on supprime l'éventuelle cellule
			if (n<2 || n>3)
				config_new[i][j] = false;

			// Si trois voisins, on crée une cellule
			if (n==3)
				config_new[i][j] = true;
		}
	}

	// On copie config_new dans config
	config = config_new;
}


void jeu_vie::affichage(std::ostream &flux) const
{
	for (int i=0; i<H; i++){
		for (int j=0; j<L; j++)
			flux << (config[i][j] ? "X" : ".");	  
		flux << "\n";
	}
}


int jeu_vie::nb_cellules() const{
	// N va servir à compter le nombre de cellules
	int N = 0;
	for (int i=0; i<H; i++)
		for (int j=0; j<L; j++)
			// Si une particules est présente en i,j, on ajoute 1 à N
			if (config[i][j])
				N++;

	return N;
}

