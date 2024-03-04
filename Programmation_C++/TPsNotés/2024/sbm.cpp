#include "sbm.hpp"

#include <string>

using namespace std;

// question 3
Graph::Graph(MatInt A, bool directed, VectInt Z): m_adj(A), m_directed(directed), m_Z(Z){
    //
    if (Z.size()==0) {
        m_Z(A.cols(), 0);
    } else {
        m_Z(Z);
    }
};

// question 4
Graph::Graph(istream &flux){
    int n;
    flux >> n;

    m_adj = MatInt::Zero(n,n);
    m_Z = VectInt::Zero(n);

    flux >> m_directed;

    for(int i=0 ; i<n ; i++){
        for(int j=0 ; j<n ; j++){
            flux >> m_adj(i,j);
        }
    }

    if (!flux.eof()) {
        for(int i=0 ; i<n ; i++)    flux >> m_Z(i);
    }
    
};

// question 8
ostream & operator<<(ostream &out, const Graph &G){
    out << G.nb_noeuds() << "\n";

    out << G.get_m_directed() << "\n";

    out << G.get_m_adj() << "\n";

    for(int i=0 ; i<G.nb_noeuds() ; i++)    out << G.get_m_Z()[i] << " ";

    return out;
};

// question 12
// je ne comprends pas bien le calcul de la proba à partir de notre alpha
Graph SBM::generate_graph(int n, std::mt19937_64 &G) const {

    discrete_distribution D(m_pi.begin(), m_pi.end());
    VectInt Z(n);
    for(int i=0 ; i<n ; i++)    Z(i) = D(G);


    bernoulli_distribution Ber(m_alpha);
    MatInt A(n,n);

    for(int i=0 ; i<n ; i++){
        for(int j=0 ; j<n ; j++){
            // pas compris...
            A(i,j) = Ber(G);
        }
    }

    Graph new_graph(A, m_directed, Z);
    return new_graph;
};

// question 14
MatInt Graph::one_hot_Z() const {
    MatInt one_hot = MatInt::Zero(nb_noeuds(), nb_blocs());

    for(int i=0 ; i<nb_noeuds() ; i++){
        one_hot(i,m_Z(i)) = 1;
    }

    return one_hot;
};

// question 16
VectInt Graph::count_statistics_s() const{
    return one_hot_Z().colwise().sum();
};
MatInt Graph::count_statistics_a() const{
    int K = nb_blocs();

    MatInt A(m_adj);
    for(int i=0 ; i<nb_noeuds() ; i++){
        A(i,i)=0;
    }

    MatInt Z = one_hot_Z();
    MatInt a = Z.transpose()*A*Z;

    if (!m_directed){
        for(int i=0 ; i<K ; i++){
            a(i,i) /= 2;
        }
    }

    return a;
};
/* Je ne sais pas comment faire -m_adj sans boucle for */
MatInt Graph::count_statistics_b() const{
    int K = nb_blocs();

    MatInt A(m_adj);
    for(int i=0 ; i<nb_noeuds() ; i++){
        A(i,i)=1;
    }
    MatInt ones = MatInt::Ones(nb_noeuds(), nb_noeuds());

    MatInt Z = one_hot_Z();
    MatInt b = Z.transpose()*(ones-A)*Z;

    if (!m_directed){
        for(int i=0 ; i<K ; i++){
            b(i,i) /= 2;
        }
    }

    return b;
};