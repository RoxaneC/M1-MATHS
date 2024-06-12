//NOM: CELLIER
//PRENOM: Roxane

// question 1
#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>

//Prototypes: NE PAS TOUCHER
template <class Domain, class Value> 
    bool test_if_contains(const Domain & D, const Value & v);
template <class Domain, class Function> 
    class PiecewiseFn;
template <class Value> 
    class Affine_Fn;
 
// CLASSE SEGMENT: NE PAS TOUCHER !!!! C'EST MON CADEAU DE FIN D'ANNEE
struct Segment {
    double left;
    double right;
    Segment(double a=0.,double b=1.): left(a), right(b) {};
    bool contains(double x) const { return (left<x) && (x<right); } 
};
std::istream & operator >>(std::istream & is, Segment & S) {
    return is >> S.left >> S.right;
}
// Fin de la classe segment.
    

//----------------------------Debut du code à compléter:

    
template <class Domain, class Value>
bool test_if_contains(const Domain & D, const Value & v) {
    // COMPLETER
    // question 2
    return D.contains(v);
}

template <class Domain, class Function> 
class PiecewiseFn {
    private:
        std::vector< std::pair<Domain, Function> > pieces;
        double default_v;
    public:
        PiecewiseFn(const double & v=0);
        void add_piece(const Domain & t, const Function & f);
        template <class Argument> double operator() (const Argument &) const;
        // question 4
        int nb_morceaux() const {	return pieces.size(); };
};


template <class Value> 
class Affine_Fn {
    private:
        Value a;
        Value b;
    public:
    // question 7
        Affine_Fn(const Value & a0, const Value & b0): a(a0), b(b0) {};
        Value operator () (const Value & x ) const {	return a*x+b; };
};


// question 3
template <class Domain, class Function> 
PiecewiseFn<Domain, Function>::PiecewiseFn(const double & v): default_v(v), pieces(){};

// question 5
template <class Domain, class Function> 
void PiecewiseFn<Domain, Function>::add_piece(const Domain & t, const Function & f){
	std::pair<Domain, Function> p = std::make_pair(t,f);
	pieces.push_back(p);
}

// question 6
template <class Domain, class Function> 
template <class Argument>
double PiecewiseFn<Domain, Function>::operator()(const Argument & x) const{
	auto it = std::find_if(	pieces.begin(), pieces.end(),
							[x](const std::pair<Domain, Function> &p){	return test_if_contains(p.first, x); });
							
	double res = (it != pieces.end()) ? (*it).second(x) : default_v;
	return res;
}









