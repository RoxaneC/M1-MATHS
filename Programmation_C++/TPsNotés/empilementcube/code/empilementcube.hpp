


#ifndef EMPILEMENTCLASS
#define EMPILEMENTCLASS 

#include <vector>
#include <iostream>
class Cube {
	public:
		Cube(double posx=0.,double posy=0.,double w0=1.): x(posx), y(posy), width(w0) {}
		friend std::ostream & operator<<( std::ostream &, const Cube &);
		friend std::istream & operator>>( std::istream &, Cube &);
		friend class Empilement;
	private:
		double x;
		double y;
		double width;
};

class Empilement {
	public:
	// Constructeur
		Empilement(): vcube(), barycenter_above() {}
		Empilement(int nb,double posx=0.,double posy=0.,double w=1.): vcube(nb,Cube(posx,posy,w)), barycenter_above(nb-1,std::make_pair(posx,posy)) {}
	// accesseurs et mutateurs:
		int size() const { return vcube.size();}
		double get_x(int i) const { return vcube[i].x; }
		double get_y(int i) const { return vcube[i].y; }
		double & width(int i) { return vcube[i].width; }
	// Entrées-sorties:
		friend std::ostream & operator<<( std::ostream &, const Empilement &);
		friend std::istream & operator>>( std::istream &, Empilement &);
	// Algorithmique:
		double height() const;
		void clear() { vcube.clear(); barycenter_above.clear();}
		bool add_new_cube(double posx,double posy,double hw);
		void compute_barycenters();
		bool is_stable() const;
	// opérateurs:
		friend Empilement operator+(const Empilement &,const Empilement &);
	private:
		std::vector<Cube> vcube;//taille: nb de cubes
		std::vector< std::pair<double,double> > barycenter_above; 
			//taille: nb de cubes -1
};
#endif
