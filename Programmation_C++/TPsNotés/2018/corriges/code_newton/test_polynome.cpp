#include "polynome.hpp"
#include "newton.hpp"
#include <iostream>
#include <vector>

int main() {
	std::vector<double> cP {-12., 3., -16., 4., -4., 1.};
	Polynome<double> P(cP);
	
	double resultat;
	for (double x_init=-10.; x_init<10. ; x_init += 0.1)
	{
		resultat = newton_method(P,x_init,1000);
		std::cout << "Zéro estimé à partir du point initial " << x_init << " :\t" << resultat << "\t(valeur du polynôme: " << P(resultat) <<")\n";
	}
	return 0;
}
