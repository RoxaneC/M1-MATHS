#include "interpolation.hpp"

#include <algorithm>
#include <numeric>

using namespace std;

//constructeurs
LagrangeInterpolation::LagrangeInterpolation(double u, double delta, const vector<double> & y): x_values(y.size()), y_values(y) {
	for (size_t i = 0; i < x_values.size(); i++)
	{
		x_values[i]=u+delta*i;
	}
    // for necessaire car i apparaît dans la formule. POssibilité avec std::iota mais laborieux.
}


// entrées-sorties:
std::ostream & operator << (std::ostream & os, const LagrangeInterpolation & P) {
	os << P.x_values.size() << "\n";
	for (size_t i = 0; i < P.x_values.size(); i++)
	{
		os << P.x_values[i] << " " << P.y_values[i] << "\n";
	}
    // for nécessaire car il faut parcourir deux conteneurs en meme temps. Evitable à partir de C++20 avec views::zip.
	return os;
}

std::istream & operator >> (std::istream & is, LagrangeInterpolation & P) {
	size_t n;
	is >> n;
	P.x_values.resize(n);
	P.y_values.resize(n);
	for (size_t i = 0; i < n; i++)
	{
		is >>P.x_values[i] >> P.y_values[i];
	}
	return is;
}

// Methodes const

double LagrangeInterpolation::lower_bound() const {
	return *min_element(x_values.begin(), x_values.end());
}

double LagrangeInterpolation::upper_bound() const {
	return *max_element(x_values.begin(), x_values.end());
}

double LagrangeInterpolation::eval_basis_polynomial(size_t k,double z) const {
	// mal défini si z vaut l'un des x_values
	double result=1.;
	double val_k = x_values[k];
	auto prod = [=](double p,double x) { return p*(z-x)/(val_k-x);};
	result= accumulate(
		x_values.begin(),x_values.begin()+k,
		result, prod);
	result= accumulate(
		x_values.begin()+k+1,x_values.end(),
		result, prod);
	/* boucles équivalentes:
	for (size_t i = 0; i < k; i++)
	{
		result *= (z-x_values[i])/(val_k-x_values[i]);
	}
	for (size_t i = k+1; i < x_values.size(); i++)
	{
		result *= (z-x_values[i])/(val_k-x_values[i]);
	}*/
	return result;
}

double LagrangeInterpolation::operator ()(double z) const {
	// on vérifie si z apparaît dans x_values
    if ( x_values.size() == 0 ) {
        return 0.;
    };
	auto find_z= find(x_values.begin(), x_values.end(), z);
	if( find_z != x_values.end() ){
		return y_values[distance(x_values.begin(),find_z)];
	}
	else {
		double result=0.;
		for (size_t i = 0; i < y_values.size(); i++)
		{
			result += y_values[i]*eval_basis_polynomial(i,z);
		}
		return result;
	}
}

// methodes non_const:
bool LagrangeInterpolation::add_point(double x, double y) {
	if ( find(x_values.begin(),x_values.end(),x) != x_values.end() )
	{
		cout << "  [Warning: no point added]  ";
		return false;
	}
	else {
		x_values.push_back(x);
		y_values.push_back(y);
		return true;
	}
}

// Fonctions

LagrangeInterpolation operator + (const LagrangeInterpolation & P1, const LagrangeInterpolation & P2) {
    LagrangeInterpolation result;
    result.x_values.resize( P1.nb_points() + P2.nb_points() );
    result.y_values.resize( P1.nb_points() + P2.nb_points() );
    copy( P1.x_values.cbegin(), P1.x_values.cend(), result.x_values.begin() );
    copy( P1.y_values.cbegin(), P1.y_values.cend(), result.y_values.begin() );
    copy( P2.x_values.cbegin(), P2.x_values.cend(), result.x_values.begin()+P1.nb_points() );
    copy( P2.y_values.cbegin(), P2.y_values.cend(), result.y_values.begin()+P1.nb_points() );
    transform( 
        result.x_values.cbegin(), result.x_values.cbegin()+P1.nb_points(),
        result.y_values.cbegin(),
        result.y_values.begin(),
        [&](double x, double y) { return y+P2(x); }
        );
    transform( 
        result.x_values.cbegin()+P1.nb_points(), result.x_values.cend(),
        result.y_values.cbegin()+P1.nb_points(),
        result.y_values.begin(),
        [&](double x, double y) { return y+P1(x); }
        );
    return result;
}
