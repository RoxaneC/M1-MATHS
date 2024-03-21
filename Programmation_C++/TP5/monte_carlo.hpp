#ifndef MY_MONTE_CARLO
#define MY_MONTE_CARLO

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

#endif
