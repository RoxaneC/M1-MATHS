#include "monte_carlo.hpp"
#include "pi.hpp"

#include <iostream>
#include <cmath>
#include <random>
#include <fstream>

using namespace std;
auto id = [](auto x){	return x;};

// question 5.11
void Histogramme::operator+=(double x){
	if (x>=lbound && x<=ubound){
		int k = floor((x-lbound)/box_width);
		echantillon[k]++;
	}
};
void Histogramme::operator/=(unsigned int n){
	for(int i=0 ; i<nb_boxes ; i++){
		echantillon[i]/=double(n);
	}
};

// question 5.12
ostream & operator<<(ostream &o,const Histogramme &H){
	int compt = 0;
	for(double d : H.echantillon){
		o << compt << "\t" << d << "\n";
		compt++;
	}
	return o;
};

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
	DoubleMeanVar I1;
	uniform_real_distribution<double> X(0,1);
	MonteCarlo(I1, X, [](double x){return log(1+x*x);}, Gen, 100000);
	cout << "5.9.1)\tApproxiation de l'intégrale sur [0,1] de ln(1+x*x) : " << I1.get_m() << "\n";
	double I1_bas = I1.get_m() - 1.96 * sqrt(I1.get_v()/100000.);
	double I1_haut = I1.get_m() + 1.96 * sqrt(I1.get_v()/100000.);
	cout << "\tIntervalle de confiance : [" << I1_bas << " ; " << I1_haut << "]\n";

	DoubleMeanVar I2;
	uniform_real_distribution<double> Y(0,1);
	exponential_distribution<double> Z(1);
	auto CoupleXY = [&](mt19937 & G) {	return make_pair(Y(G),Z(G)); };
	auto Function_to_evaluate = [&](pair<double,double> p) {	return log(1+ p.first*p.second); };
	MonteCarlo(I2, CoupleXY, Function_to_evaluate, Gen, 100000);
	cout << "5.9.2)\tApproxiation de l'intégrale sur Rx[0,1] de ln(1+x*y)*exp(-x) : " << I2.get_m() << "\n";
	double I2_bas = I2.get_m() - 1.96 * sqrt(I2.get_v()/100000.);
	double I2_haut = I2.get_m() + 1.96 * sqrt(I2.get_v()/100000.);
	cout << "\tIntervalle de confiance : [" << I2_bas << " ; " << I2_haut << "]\n";

	// question 5.13
	Histogramme H(-3, 3, 50);
	int nb_ech = 100000;
	normal_distribution<double> N;
	MonteCarlo(H, N, id, Gen, nb_ech);

	ofstream file("Histogramme.dat");
	file << H;
	file.close();

	
	return 0;
}
