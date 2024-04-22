#ifndef MY_MONTE_CARLO
#define MY_MONTE_CARLO

#include <vector>
#include <iostream>

// question 5.1
template <class Stat, class RV, class Meas, class RNG>
void MonteCarlo(Stat & result, RV &X, const Meas &f, RNG &G, long int n){
	for(long int i=0 ; i<n ; i++){
		result += f(X(G));
	}
	result /= double(n);
};

class DoubleMeanVar{
	protected:
		double m;
		double v;
		
	public:
		// question 5.5
		DoubleMeanVar(double x=0.): m(x), v(0){}; 
		// question 5.6
		void operator+=(double x){	m += x;	v += x*x; };
		void operator/=(double n){	m /= n;	v /= n; };
		// question 5.7
		double get_m() const { return m; };
		double get_v() const { return v - m*m; };

};

class Histogramme{
	protected:
		std::vector<double> echantillon;
		unsigned int nb_boxes; // nombre de boites
		double lbound; // borne inf de l'intervalle
		double ubound; // borne sur de l'intervalle
		double box_width; // largeur des boites

	public:
		// question 5.10
		Histogramme(double min_intervalle, double max_intervalle, unsigned int n):
				echantillon(n),
				lbound(min_intervalle),
				ubound(max_intervalle),
				nb_boxes(n),
				box_width((max_intervalle-min_intervalle)/n)
				{};
		// question 5.11
		void operator+=(double x);
		void operator/=(unsigned int n);
		// question 5.12
		friend std::ostream & operator<<(std::ostream &o, const Histogramme &H);

};

#endif
