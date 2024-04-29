//NOM:
//PRENOM:
//# étudiant:

//à compléter

using namespace std;

#include "fma.hpp"
#include "geometry.hpp"
#include <cmath>

int main() {
	// Section 2.1:
    // question 6 : ok
    Finite_atomic_measure<int> mu;
    mu.add_mass( 3, 1.);
    mu.add_mass( 5, 2.);
    mu.add_mass( 8, 0.5);
    cout << "*** Masse totale: " << mu.total_mass()<< "\n";
    cout << "*** Nb points: " << mu.nb_of_atoms() << "\n";
    cout << "*** Mesure nu:\n" << mu << "\n";
    //fin section 2.1
    
    // Section 2.2: 
    //question 9 & 10 : ok
    Segment<int> S1(4,9), S2(-3,6), S3(-3,0);
	cout << "*** Mesure mu([4,9]): " << mu.measure(S1) << "\n";//attendu: 2.5
	cout << "*** Mesure mu([-3,6]): " << mu.measure(S2) << "\n";//attendu: 3.
	cout << "*** Mesure mu([-3,0]): " << mu.measure(S3) << "\n";//attendu: 0.
    cout << "*** Intégrale de sqrt: " << mu.integral([](int n) { return sqrt(n); })<< "\n\n";     // 7.6184
	// fin section 2.2
    
    // Section 2.4, question 14:
    // à vous d'écrire !!!
    auto f = [](const int &x){    return (x-4)*(x-4) -M_PI; };
    Finite_atomic_measure<double> nu = image(mu, f);
    cout << "*** Mesure image de mu:\n" << nu << "\n";

    // BONUS : Section 2.5
    // à vous d'écrire !!!
    return 0;
}
