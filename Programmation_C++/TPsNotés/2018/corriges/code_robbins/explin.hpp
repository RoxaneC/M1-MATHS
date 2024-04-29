#ifndef EXPCOMBILIN_CLASS
#define EXPCOMBILIN_CLASS

class ExpCombiLin {
	private:
		unsigned k;
		double * alpha;	//tableau des alpha_i
		double * beta; //tableau des beta_i
	public: 
		ExpCombiLin(unsigned n);//constructeur
		// Rule of three:
		ExpCombiLin(const ExpCombiLin &);//copie
		~ExpCombiLin() { delete [] alpha; delete []beta;}
		ExpCombiLin & operator =(const ExpCombiLin &);
		//Accesseur
		double coeff(unsigned i) const { return alpha[i];} //accesseur alpha
		double & coeff(unsigned i) { return alpha[i];} //accesseur alpha
		double exponent(unsigned i) const { return beta[i];}//accesseur beta
		double & exponent(unsigned i) { return beta[i];} //accesseur alpha
		// Evaluation:
		double operator() (double x) const;
		
};

#endif
