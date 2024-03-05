// -------------
// GLEYZE
// CONSTANTIN
// 21217567
// -------------

#include "sbm.hpp"

int main(){
	
	//Question 9
	MatInt A;
	A =MatInt::Zero(3,3);
	VecInt V;
	V = VecInt::Zero(3);
	
	A(0,0) = 0;
	A(0,1) = 1;
	A(0,2) = 1;
	
	A(1,0) = 1;
	A(1,1) = 0;
	A(1,2) = 0;
	
	A(2,0) = 1;
	A(2,1) = 0;
	A(2,2) = 0;
	
	V[2] =1;
	
	Graph simple_graph_directed (A,true,V);
	Graph simple_graph_undirected (A,false,V);
	
	std::ifstream fichier("graph.dat");
	Graph f_graph(fichier);
	fichier.close();
	
	std::cout << "Graphe simple_graph_directed : \n" << simple_graph_directed << "\n";
	std::cout << "Graphe simple_graph_undirected : \n" << simple_graph_undirected<< "\n";
	std::cout << "Graphe f_graph : \n" << f_graph<< "\n";
	
	//Question n°13
	std::mt19937_64 G(time(nullptr));
	SBM my_SBM({0.5,0.3,0.2},0.5,true);
	Graph G_Graph= my_SBM.generate_graph(10,G);
	
	//Question n°15
	
	MatInt Test;
	Test = f_graph.one_hot();
	std::cout << "L'encodage one_hot des variables latentes de f_graph est : \n";
	for (int i=0; i<Test.cols();i++){
		for (int j=0; j<Test.rows();j++){
			std::cout << Test(j,i) << " ";
		}
		std::cout << "\n";
	}	
	return 0;}
	
