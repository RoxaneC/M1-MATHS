#include <iostream>
#include <random>
#include "empilementcube.hpp"

using namespace std;
typedef std::mt19937 MT;

int main() {
	MT G(time(nullptr));
	const uint NS=100;
	Empilement E;
	
	double epsilon=0.25;
	uniform_real_distribution<double> Noise(-epsilon,epsilon);
	double w0=1.;
	double moy=0.;
	double hmoy=0.;
	double lastpos1=0.;
	double lastpos2=0.;
	for (uint k = 0; k < NS; k++)
	{
		E.clear();
		while( E.add_new_cube( lastpos1,lastpos2 ,w0) ) {
			lastpos1 += Noise(G);
			lastpos2 += Noise(G);
		}
		moy += E.size();
		hmoy += E.height();
	}
	cout << "Nombre moyen de cubes = " << moy/NS << "\n";
	cout << "Hauteur moyenne = " << hmoy/NS << "\n";
	cout << "Ratio = " << hmoy/moy << "\n";
	
	bernoulli_distribution U(0.5);
	double w1=1.1;
	double w2=0.9;
	moy=0.;
	hmoy=0.;
	lastpos1=0.;
	lastpos2=0.;
	for (uint k = 0; k < NS; k++)
	{
		E.clear();
		if( U(G) ) w0=w1; else w0=w2;
		while( E.add_new_cube(lastpos1,lastpos2,w0) ) {
			if( U(G) ) w0=w1; else w0=w2;
			lastpos1 += Noise(G);
			lastpos2 += Noise(G);
		}
		moy += E.size();
		hmoy += E.height();
	}
	cout << "Nombres moyens de cubes = " << moy/NS << "\n";
	cout << "Hauteur moyenne = " << hmoy/NS << "\n";
	cout << "Ratio = " << hmoy/moy << "\n";
	
	return 0;
}
