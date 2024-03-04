#include "empilementcube.hpp"
#include <numeric>
#include <iterator>
#include <algorithm>
using namespace std;

std::ostream & operator<<( std::ostream & out, const Cube & C) {
	return out << C.x << " " << C.y << " " << C.width;
}
std::istream & operator>>( std::istream & in, Cube & C) {
	return in >> C.x  >> C.y  >> C.width;
}


ostream & operator<<( ostream & out, const Empilement & E) {
	out << E.vcube.size() << "\n";
	for (unsigned int i = 0; i < E.vcube.size(); i++)
	{
		out << E.vcube[i] <<"\n";
	}
	/* la boucle peut être remplacée par:
	ostream_iterator<Cube> out_it(out,"\n");
	copy(E.vcube.begin(),E.vcube.end(),out_it)
	* */
	return out;
}

istream & operator>>( istream & in, Empilement & E){
	int nb_cubes;
	in >> nb_cubes;
	E.vcube.resize(nb_cubes);
	for (int i = 0; i < nb_cubes; i++)
	{
		in >> E.vcube[i];
	}
	/* la boucle peut être remplacée par:
	copy_n(istream_iterator<Cube>(in),nb_cubes,E.vcube.begin());
	* */
	E.compute_barycenters();
	return in;
}

double Empilement::height() const { 
	return std::accumulate(
				vcube.begin(),vcube.end(),
				0.,
				[](double x, const Cube & c) { return x+c.width; }
			);
}

bool Empilement::add_new_cube(double pos_x,double pos_y,double w) {
	vcube.emplace_back(pos_x,pos_y,w);
	/* emplace_back est une alternative à
	 * vcube.push_back(Cube(pos_x,pos_y,w));
	 * qui parfois accélère un petit peu les allocations mémoires.
	 * */
	compute_barycenters();
	return is_stable();
}

void Empilement::compute_barycenters() {
	barycenter_above.resize(vcube.size()-1);
	double sum_x_above = 0.;
	double sum_y_above = 0.;
	double mass_above =0.;
	for (int i = vcube.size()-2; i >=0 ; --i)
	{
		double m=vcube[i+1].width*vcube[i+1].width*vcube[i+1].width;
		sum_x_above += vcube[i+1].x*m;
		sum_y_above += vcube[i+1].y*m;
		mass_above += m;
		barycenter_above[i] =make_pair(sum_x_above/mass_above,sum_y_above/mass_above);
	}
	return;
}

bool Empilement::is_stable() const {
	if( vcube.size()<=1) return true; 
	else {
		for (int i = vcube.size()-2; (i >= 0) ; --i)
		{
			if( (barycenter_above[i].first >= vcube[i].x+0.5*vcube[i].width) 
				|| (barycenter_above[i].first <= vcube[i].x-0.5*vcube[i].width)
				|| (barycenter_above[i].second >= vcube[i].y+0.5*vcube[i].width)
				|| (barycenter_above[i].second <= vcube[i].y-0.5*vcube[i].width)
				)
			{
				return false;
			}
		}
		return true;
	}
}


Empilement operator+(const Empilement & E1,const Empilement & E2) {
	Empilement E(E1.size()+E2.size());
	copy(E1.vcube.begin(),E1.vcube.end(),E.vcube.begin());
	copy(E2.vcube.begin(),E2.vcube.end(),E.vcube.begin()+E1.size());
	E.compute_barycenters();
	return E;
}
