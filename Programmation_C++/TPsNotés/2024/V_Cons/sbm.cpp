// -------------
// GLEYZE
// CONSTANTIN
// 21217567
// -------------


#include "sbm.hpp"

//Question 2 et 3

Graph::Graph(const MatInt & M, const bool & b, const VecInt &V):m_adj(M),m_directed(b),m_Z(V){
	if(V.size()==0){
		int cols = M.cols();
		
		m_Z = VecInt::Zero(cols);}
}

//Question 4
Graph::Graph (std::istream & flux):m_adj(),m_directed(),m_Z(){
	int taille;
	flux >>taille;
	
	bool direction;
	flux >> direction;
	
	m_directed=direction;
	m_adj = MatInt::Zero(taille,taille);
	m_Z =VecInt::Zero(taille);
		
	int temporaire;
	for(int i=0; i<taille; i++){
		for (int j=0; j<taille; j++){
			flux >> temporaire;
			if (temporaire ==1){m_adj(i,j)=temporaire;}
		}
	}
	
	if (flux.eof() == false){
		for (int i=0; i<taille;i++){
			flux >> temporaire;
			m_Z(i)=temporaire;
		}
	}
	
}

//Question 7
int Graph::nb_blocs() const {
	
	int blocs;
	blocs = *std::max_element(m_Z.begin(),m_Z.end())+1;
	
	return blocs;}

//Question 8
std::ostream & operator << (std::ostream & o, const Graph & G){
	o << G.m_adj.cols() << "\n";
	o<< G.m_directed << "\n";
	
	for (int i=0; i<G.m_adj.rows();i++){
		for (int j=0; j<G.m_adj.cols();j++){
			o<< G.m_adj(i,j) << " ";
		}
		o << "\n";
	}
	
	for (int i=0; i<G.m_adj.rows();i++){
		o << G.m_Z[i] << " ";
	}
	
	o << "\n";
	
	return o;}
	
//Question n°12
Graph SBM::generate_graph(const int & n, std::mt19937_64 & G){

	std::discrete_distribution<int> Loi(m_pi.begin(),m_pi.end());
	
	VecInt Z;
	Z = VecInt::Zero(n);
	double proba;
	
	for (int i=0; i<n; i++){
		Z(i) = Loi(G);}
		
	MatInt A;
	A =MatInt::Zero(n,n);
	
	for (int i=0; i<n; i++){
		for (int j=0; j<n; j++){
			if (i!=j){
				proba = m_alpha;
				proba = pow(proba,double(i*j));
				std::bernoulli_distribution Ber(proba);
				int result;
				result = Ber(G); 
				if (result ==1){A(i,j) = 1;}
				else {A(i,j)=0;}
			}	
			else if (i==j){A(i,j)=0;};
		}
	}
	
	Graph M(A,m_directed,Z);
	return M;
}

//Question n°14

MatInt Graph::one_hot() const{
	int bloc;
	bloc = nb_blocs();
	MatInt M;
	std::cout << "Nb de colonnes : " << m_adj.cols() << "\n";
	M= MatInt::Zero(bloc,m_adj.cols());
	for (int i=0;i<m_adj.cols();i++){
		for (int j=0; j<bloc;j++){
			if (m_Z[i] ==j){M(j,i)=1;}
			else {M(j,i)=0;}
		}
	}
	
	return M;
}

//Question n°16

std::vector<int> Graph::count_statistics_s() const{
	MatInt M; 
	M = one_hot();
	int stat = 0;
	std::vector <int> v(M.cols());
	
	for(int i=0; i<M.cols();i++){
		stat=0;
		for (int j=0; j<M.rows();j++){
			stat += M(j,i);
		}
		v.push_back(stat);
	}

return v; }

//Question 16 
MatInt Graph::count_statistics_a() const{
	
	MatInt M; 
	M = one_hot();
	int stat = 0;
	
	MatInt Result;
	Result = MatInt::Zero(M.cols(),M.cols());
	
	for(int i=0; i<M.cols();i++){
		for (int j=0; j<M.cols();j++){ 
			stat=0;
			for (int l=0; l<M.rows();l++){
				stat += M(l,j)*M(l,i)*m_adj(j,i);
			}
		Result(j,i)=stat;
		}
		
	}
	
	return Result;}


//Question 16 
MatInt Graph::count_statistics_b() const{
	
	MatInt M; 
	M = one_hot();
	int stat = 0;
	
	MatInt Result;
	Result = MatInt::Zero(M.cols(),M.cols());
	
	for(int i=0; i<M.cols();i++){
		for (int j=0; j<M.cols();j++){ 
			stat=0;
			for (int l=0; l<M.rows();l++){
				stat += M(l,j)*M(l,i)*(1-m_adj(j,i));
			}
		Result(j,i)=stat;
		}
		
	}
	
	return Result;}
					
