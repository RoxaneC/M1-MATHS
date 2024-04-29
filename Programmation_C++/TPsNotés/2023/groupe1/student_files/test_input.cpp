//NOM:
//PRENOM:
//# étudiant: 

//à compléter

using namespace std;

#include "fma.hpp"
#include "geometry.hpp"
#include <fstream>
#include <cmath>

int main() {
	
	//Section 2.3:
	// question 12
	Finite_atomic_measure<double> mu;
	ifstream file("atomic_data.txt");
	file >> mu;
    file.close();
    cout << "*** Masse totale: " << mu.total_mass()<< "\n";         // 42.2503
    Segment<double> S1(-3.,1.5), S2(0.5,4.2);
	cout << "*** Mesure mu([-3,1.5]): " << mu.measure(S1) << "\n";     // 34.0778
	cout << "*** Mesure mu([0.5,4.2]): " << mu.measure(S2) << "\n";    // 13.4099

	
	//Section 2.4:
	// à vous d'écrire
    // question 15
    auto f = [](const double &x){    return int(floor(x)); };
    Finite_atomic_measure<int> nu = image(mu, f);
    Segment<int> S3(0,2), S4(-10,-10), S5(10,10);
	cout << "*** Mesure nu({0,1,2}): " << nu.measure(S3) << "\n";     // 16.4031
	cout << "*** Mesure nu({-10,10}): " << nu.measure(S4)+nu.measure(S5) << "\n";     // 0 (logique)
	cout << "*** Mesure nu: " << nu.total_mass() << "\n";     // 42.2503
    
    return 0;
}
