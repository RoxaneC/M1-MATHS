#include "monte_carlo.hpp"
#include "pi.hpp"

#include <iostream>
#include <cmath>

using namespace std;

int main(){
	// question 5.4
	SquareInDisk A;
	double pi_approx;
	
	mt19937 Gen(time(nullptr));
	cout << "5.4)";
	for(int n : {1000,10000,100000}){
		pi_approx = 0;
		MonteCarlo(pi_approx, A, [](double x){return 4*x;}, Gen, n);
		cout << "\tApproximation de pi sur " << n << " échantillons : " << pi_approx << "\n";
	}
	
	// question 5.8
	DoubleMeanVar pi_approx2;
	MonteCarlo(pi_approx2, A, [](double x){return 4*x;}, Gen, 100000);
	double I_bas = pi_approx2.get_m() - 1.96 * sqrt(pi_approx2.get_v()/100000.);
	double I_haut = pi_approx2.get_m() + 1.96 * sqrt(pi_approx2.get_v()/100000.);
	cout << "5.8)\tIntervalle de confiance de pi : [" << I_bas << " ; " << I_haut << "]\n";
	
	// question 5.9
	auto CoupleXY = [&](mt19937 & G) {	return make_pair(X(G),Y(G)); };
	//auto Function_to_evaluate = [&](pair<double,double> p) {	return ln(1+ p.first*p.second)*exp(-p.first); };
	
	return 0;
}
