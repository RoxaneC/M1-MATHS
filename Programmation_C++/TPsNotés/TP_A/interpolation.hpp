//fichier interpolation.hpp
#ifndef MY_LI
#define MY_LI

#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

class LagrangeInterpolation{
    private:
        std::vector<double> x_values;     //contient les x_i
        std::vector<double> y_values;     //contient les y_i
    public:
        // Constructeurs
        LagrangeInterpolation(double _u, double _delta, const std::vector<double> &_y);
        LagrangeInterpolation();

        // Méthodes
        // question 4
        int nb_points() const { return x_values.size();};
        double operator()(double x) const;     //évaluation du polynome en un point
        // question 5
        double lower_bound() const {    return *min_element(x_values.begin(), x_values.end()); };
        double upper_bound() const {    return *max_element(x_values.begin(), x_values.end()); };
        bool add_point(double x, double y);

        // Opérateurs
        friend std::ostream & operator<<(std::ostream &out, const LagrangeInterpolation &LI);
        friend std::istream & operator>>(std::istream &in, LagrangeInterpolation &LI);
        friend LagrangeInterpolation operator+(const LagrangeInterpolation &L1, const LagrangeInterpolation &L2);
};

#endif

// question 9 : SI parce que sinon ça march epas