#include "sbm.hpp"

#include <fstream>
#include <random>

using namespace std;

int main(){
    mt19937_64 G(time(nullptr));

    // question 9
    MatInt A(3,3);
    A <<    0,1,1,
            1,0,0,
            1,0,0;
    VectInt Z(3);
    Z << 0,0,1;

    Graph simple_graph_directed(A, true, Z);
    Graph simple_graph_undirected(A, false, Z);

    cout << simple_graph_directed << "\n\n";
    cout << simple_graph_undirected << "\n\n";

    ifstream f("graph.dat");
    Graph f_graph(f);
    cout << f_graph << "\n\n";
    f.close();

    // question 13
    // Pas sûr, mauvaise compréhension du calcul de la proba
    vector<double> pi{0.5 , 0.3 , 0.2};
    SBM my_sbm(pi, 0.5, true);
    Graph graph_by_sbm = my_sbm.generate_graph(10, G);
    cout << "Graph aléatoire :\n" << graph_by_sbm << "\n\n";

    // question 15
    cout << f_graph.one_hot_Z() << "\n\n";

    // question 17
    cout << "f_graph :\n";
    cout << "stat_s\n" << f_graph.count_statistics_s() << "\n";
    cout << "stat_a\n" << f_graph.count_statistics_a() << "\n";
    cout << "stat_b\n" << f_graph.count_statistics_b() << "\n\n";

    cout << "simple_graph_directed :\n";
    cout << "stat_s\n" << simple_graph_directed.count_statistics_s() << "\n";
    cout << "stat_a\n" << simple_graph_directed.count_statistics_a() << "\n";
    cout << "stat_b\n" << simple_graph_directed.count_statistics_b() << "\n\n";

    cout << "simple_graph_undirected :\n";
    cout << "stat_s\n" << simple_graph_undirected.count_statistics_s() << "\n";
    cout << "stat_a\n" << simple_graph_undirected.count_statistics_a() << "\n";
    cout << "stat_b\n" << simple_graph_undirected.count_statistics_b() << "\n\n";

    return 0;
}