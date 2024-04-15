//NOM:
//PRENOM:
//# étudiant:

//à compléter

using namespace std;

int main() {
	// Section 2.1:
    Finite_atomic_measure<int> mu;
    mu.add_mass( 3, 1.);
    mu.add_mass( 5, 2.);
    mu.add_mass( 8, 0.5);
    cout << "*** Masse totale: " << mu.total_mass()<< "\n";
    cout << "*** Nb points: " << mu.nb_of_atoms() << "\n";
    cout << "*** Mesure nu:\n" << mu << "\n";
    //fin section 2.1
    
    // Section 2.2: 
    Segment<int> S1(4,9), S2(-3,6), S3(-3,0);
	cout << "*** Mesure mu([4,9]): " << mu.measure(S1) << "\n";//attendu: 2.5
	cout << "*** Mesure mu([-3,6]): " << mu.measure(S2) << "\n";//attendu: 3.
	cout << "*** Mesure mu([-3,0]): " << mu.measure(S3) << "\n";//attendu: 0.
    cout << "*** Intégrale de sqrt: " << mu.integral([](int n) { return sqrt(n); })<< "\n";
	// fin section 2.2
    
    // Section 2.4, question 14:
    // à vous d'écrire !!!
    
    // Section 2.5
    // à vous d'écrire !!!
    return 0;
}
