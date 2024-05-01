#ifndef EXPLIN
#define EXPLIN

// question 4
class ExpCombiLin {
    private:
        unsigned k;
        double * alpha; //tableau des alpha_i
        double * beta; //tableau des beta_i
    public:
        ExpCombiLin(unsigned);  //constructeur
        double coeff(unsigned i) const {    return alpha[i]; }; //accesseur alpha
        double exponent(unsigned i) const { return beta[i]; };  //accesseur beta
        // ajouter mutateurs avec noms identiques
        double & coeff(unsigned i) {    return alpha[i]; }; //mutateur alpha
        double & exponent(unsigned i) { return beta[i]; };  //mutateur beta

        // question 5
        double operator()(double x) const;

        // question 6
        ExpCombiLin(const ExpCombiLin &e);
        ExpCombiLin & operator=(const ExpCombiLin &e);
};


#endif