
#include "quartic.hpp"
#include "gradient.hpp"
#include "vect.hpp"

#include <iostream>

using namespace std;

// question 9 + CORRECTION
class G {
    public:
        G(){};
        double operator()(const Vect<2> &v) const {   return pow(v[0],4) + pow(v[1],4) - 2*v[0]*v[0] - 2*v[1]*v[1] + v[0] + v[1]; };
		Vect<2> grad(const Vect<2> & v) const {
			Vect<2> res;
			res[0] = 4*pow(v[0],3) - 4*v[0] +1.;
			res[1] = 4*pow(v[1],3) - 4*v[1] +1.;
			return res;
		}
};

int main(){
    // question 4
    Quartic<double> q1(1);
    Quartic<double> q2(2);
    double x=0.5;
    int nb_iter = 1000;
    tuple<double, double, double> t1 = gradient_descent(q1, x, nb_iter);
    tuple<double, double, double> t2 = gradient_descent(q2, x, nb_iter);
    cout << get<0>(t1)  << ", " << get<1>(t1)  << ", " << get<2>(t1) << "\n";
    cout << get<0>(t2)  << ", " << get<1>(t2)  << ", " << get<2>(t2)  << "\n";

    // question 9
    cout << "Partie pointeur :\n";
    Vect<2> v;    G g;

    tuple<Vect<2>, double, Vect<2>> tg = gradient_descent(g, v, 100);
    cout << get<0>(tg)  << ", " << get<1>(tg)  << ", " << get<2>(tg) << "\n";

    return 0;
}