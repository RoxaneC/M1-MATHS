//NOM: CELLIER
//PRENOM: Roxane

//completer si necessaire
#include <iostream>
#include <vector>
#include <numeric>

template <class Field,int d> class LinearForm;
template <class Field,int d> std::istream & operator>> ( std::istream & is, LinearForm<Field,d> & f);

template <class Field,int d>
class LinearForm {
    private:
        std::vector<Field> coeff;
    public:
        LinearForm(): coeff(){};
        Field operator () (const std::vector<Field> & v) const; 
        //completer si necessaire
        std::istream & operator>> <>(std::istream & is, LinearForm<Field,d> & f);
};

//ecrire les codes
// question 12
template <class Field,int d>
Field LinearForm<Field, d>::operator ()(const std::vector<Field> & v) const{
	Field res;
	for(int i=0 ; i<d ; i++){
		res += coeff[i] * v[i];
	}
	
	return res;
}

template <class Field,int d> std::istream & operator>> ( std::istream & is, LinearForm<Field,d> & f);

