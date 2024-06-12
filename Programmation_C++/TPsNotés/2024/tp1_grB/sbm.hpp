#ifndef MY_GRAPH
#define MY_GRAPH

#include <Eigen/Dense> // g++ .... -I "eingen3/Eigen/Dense" -o ....
#include <Eigen/StdVector>

#include <iostream>
#include <algorithm>
#include <vector>
#include <random>

using MatDouble = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>;
using VectDouble = Eigen::Vector<double, Eigen::Dynamic>;
using MatInt = Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic>;
using VectInt = Eigen::Vector<int, Eigen::Dynamic>;

class Graph;
class SBM;

class Graph{
    //
    private:
        MatInt m_adj; // of size n*n
        bool m_directed; // orienté ou non
        VectInt m_Z; // va latente

    public:
        // question 2 et 3
        Graph(MatInt A, bool directed=true, VectInt Z={});

        // question 4
        Graph(std::istream &flux);

        // question 5
        MatInt get_m_adj() const {  return m_adj; };
        bool get_m_directed() const {   return m_directed; };
        VectInt get_m_Z() const {   return m_Z; };

        // question 6
        int nb_noeuds() const { return m_adj.cols(); };

        // question 7
        int nb_blocs() const {  return *std::max_element(m_Z.begin(), m_Z.end())+1; };

        // question 8
        friend std::ostream & operator<<(std::ostream &out, const Graph &G);

        // question 14
        MatInt one_hot_Z() const;

        // question 16
        VectInt count_statistics_s() const;
        MatInt count_statistics_a() const;
        MatInt count_statistics_b() const;
};


class SBM{
    private:
        std::vector<double> m_pi; // block proportion
        double m_alpha; // Ber param connectivité
        bool m_directed; // orienté ou non

    public:
        // question 10
        SBM(std::vector<double> pi, double alpha, bool b): m_pi(pi), m_alpha(alpha), m_directed(b){};

        // question 11
        int get_K() const { return m_pi.size(); };

        // question 12
        Graph generate_graph(int n, std::mt19937_64 &G) const;
};

#endif