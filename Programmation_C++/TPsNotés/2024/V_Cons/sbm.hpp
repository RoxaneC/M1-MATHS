// -------------
// GLEYZE
// CONSTANTIN
// 21217567
// -------------

#ifndef __GRAPH__
#define __GRAPH__


#include <Eigen/Dense>
#include <Eigen/StdVector>

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <random>
#include <cmath>

using MatDouble = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>;
using VecDouble = Eigen::Vector<double, Eigen::Dynamic>;
using MatInt = Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic>;
using VecInt = Eigen::Vector<int, Eigen::Dynamic>;

class Graph;
class SBM;

class Graph{

public : 

	Graph(const MatInt &, const bool & =true, const VecInt& =VecInt ()); //Constructeur (Q°3-4)
	Graph (std::istream &); //Constructeur (Q°4)
	
	MatInt M_Adj() const {return m_adj;} //Accesseur (Q°5)
	bool direction() const {return m_directed;} //Accesseur (Q°5)
	VecInt latent() const {return m_Z;} //Accesseur (Q°5)
	int nb_noeuds() const {return int(m_adj.cols()*m_adj.rows());}; //Methode (Q°6)
	int nb_blocs() const; //Methode (Q°7)
	
	friend std::ostream & operator << (std::ostream &, const Graph &); //Operateur (Q°8)
	MatInt one_hot() const;//Methode (Q°15)
	std::vector<int> count_statistics_s() const; //Methode (Q°16)
	MatInt count_statistics_a() const;//Methode (Q°16)
	MatInt count_statistics_b() const;//Methode (Q°16)
	
private : 
	MatInt m_adj; //of size nxn
	bool m_directed; //for directed or undirected graphs
	VecInt m_Z; //latent variables	
};

class SBM{
	
public : 
	
	friend class Graph;
	SBM(const std::vector<double> & v, const double & d, const bool & b):m_pi(v),m_alpha(d),m_directed(b){}; //Constructeur (Q°10)
	int get_K() const {return m_pi.size();}; //Accesseur (Q°11)
	Graph generate_graph(const int &, std::mt19937_64 &);//Methode (Q°12)
	
	
private : 
	std::vector<double> m_pi;
	double m_alpha;
	bool m_directed;
};

#endif
