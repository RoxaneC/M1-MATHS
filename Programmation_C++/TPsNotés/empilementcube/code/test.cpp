#include <iostream>
#include <fstream>
#include "empilementcube.hpp"

using namespace std;

int main() {
	Empilement E(5,0.,0.,1.), E1,E2;
	bool b;
	
	cout << "Empilement E: " << E;
	cout << "Hauteur de E: " << E.height() << "\n";
	
	ifstream F("example1.dat");
	F >> E1;
	F.close();
	
	cout << "\nEmpilement 1:\n" << E1;
	cout << "\nHauteur de E1: " << E1.height()<< "\n";

	cout << "L'empilement 1 est-il stable ? ";
	b=E1.is_stable();
	if (b) { cout << "Oui\n";} else { cout << "Non\n"; }
	E1.add_new_cube(0.5,1.,1.);
	b=E1.is_stable();
	if (b) { cout << "Oui\n";} else { cout << "Non\n"; }
	E1.add_new_cube(0.5,1.,2);
	b=E1.is_stable();
	if (b) { cout << "Oui\n";} else { cout << "Non\n"; }
	
	F.open("example2.dat");
	F >> E2;
	F.close();
	cout << "\nEmpilement 2:\n" << E2;
	cout << "\nHauteur de E2: " << E2.height()<< "\n";
	cout << "L'empilement 2 est-il stable ? ";
	b=E.is_stable();
	if (b) { cout << "Oui\n";} else { cout << "Non\n"; }
	
	// Test de l'opérateur +:
	Empilement E3(3,0.25,-0.25,2.);
	cout << E+E3 << "\n";
	return 0;
}
