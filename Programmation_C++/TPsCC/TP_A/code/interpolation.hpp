#ifndef LAGRANGE_INTERPOLATION_POLYNOME
#define LAGRANGE_INTERPOLATION_POLYNOME

#include <iostream>
#include <vector>

// déclarations classe et fonctions:
class LagrangeInterpolation;

std::ostream & operator << (std::ostream &, const LagrangeInterpolation &);
std::istream & operator >> (std::istream &, LagrangeInterpolation &);

LagrangeInterpolation operator + (const LagrangeInterpolation &, const LagrangeInterpolation &);

// définition de la classe:
class LagrangeInterpolation{
private:
    std::vector< double > x_values;//contient les x_i
    std::vector< double > y_values;//contient les x_i
    
    double eval_basis_polynomial(size_t,double) const;//calcule P^{(x)}_i(z)
public:
    //constructeurs
    LagrangeInterpolation() = default;
    LagrangeInterpolation(double lb, double delta, const std::vector<double> & yvalues);
    
    // methodes const
    double nb_points() const { return x_values.size(); }
    double operator()(double) const;//évaluation du polynome en un point
    double lower_bound() const;
    double upper_bound() const;
    
    bool is_valid() const;
    
    // methodes non const
    bool add_point(double, double);
	
	// liens d'amitié:
	friend std::ostream & operator << (std::ostream &, const LagrangeInterpolation &);
	friend std::istream & operator >> (std::istream &, LagrangeInterpolation &);
    friend LagrangeInterpolation operator + (const LagrangeInterpolation &, const LagrangeInterpolation &);
};

#endif

