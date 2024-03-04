#include "interpolation.hpp"

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;


int main() {
	const LagrangeInterpolation P(0., 0.25,{1., 3., 2., 4.});
	cout << "Voici le polynome lu dans points.dat:\n" << P << "-----\n";
/* Affichage attendu pour P:
    5 !non 4
    0 1
    0.25 3
    0.5 2
    0.75 4
*/

	cout << "Le polynome P contient " << P.nb_points() << " couples \n";
	cout << "L'abscisse minimale est : " << P.lower_bound() << "\n"; //0
	cout << "L'abscisse maximale est : " << P.upper_bound() << "\n"; //0.75
	cout << "L'évaluation en z=0.75 donne : " << P(0.75) << "\n"; // 4.
	cout << "L'évaluation en z=0.4 donne : " << P(0.4) << "\n"; //2.376
	cout << "L'évaluation en z=0.1 donne : " << P(0.1) << "\n"; //2.544
    LagrangeInterpolation Q(0., 0.25,{1., 3., 2., 4.});
	cout << "Ajout de (0.5,7) à Q ? " << Q.add_point(0.5, 7.) << "\n"; //message d'erreur et n'ajoute pas de point
	cout << "Ajout de (0.4,1.2) à Q? " << Q.add_point(0.4, 1.2) << "\n"; //1
	cout << "Nouvel objet Q: "<< Q;
	cout << "L'évaluation de Q en z=0.75 donne: " << Q(0.75) << "\n"; //4
	cout << "L'évaluation de Q en z=0.4 donne: " << Q(0.4) << "\n"; //1.2
	cout << "L'évaluation de Q en z=0.1 donne: " << Q(0.1) << "\n"; //4.728
	return 0;
}

