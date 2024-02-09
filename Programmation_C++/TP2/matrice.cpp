#include <Eigen/Dense> // mettre '-I /usr/include/eigen3/' à la compilation !!!
#include <Eigen/Sparse>
#include <Eigen/Eigenvalues>

#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <random>
#include <ctime>

using namespace std;
typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> MatrixDouble;

// question 2.4(13)
class Histogramme{
    private:
        double a;       // borne inf
        double b;       // borne sup
        double delta;       // écart entre les bornes
        vector<int> bars;       // stock des points par segment
        int nb_out;     // nb de points hors de l'intervalle
    public:
        // Constructeur
        Histogramme(double _a, double _b, int _N): a(_a), b(_b), delta((b-a)/N), bars(N,0), nb_out(0) {};

        // Méthodes
        bool operator+=(double x);      // ajoute un pt dans la barre correspondante
        void print(ofstream & out) const;       // affiche les valeurs de l'histo (?)
        void reset();       // réinitialise à 0 en gardant les paramètres

        // Accesseurs
        double lower_bound() const;     // accède à a
        double upper_bound() const;     // accède à b
        double nb_boxes() const;        // accède au nb de segments
        int out_of_domain() const;      // accède à nb_out
};

// question 1.1
/* question 1.2 :
* Il y a n*n calculs ?
* On rajoute le cas n==1 pour éviter l'opération finale M*Id qui n'est pas utile */
MatrixDouble puissance_lente(const MatrixDouble & M, int n){
    if (n==0){  return MatrixDouble::Identity(M.rows(),M.cols()); }
    else if (n==1){ return M; }
    else {
        MatrixDouble N(M.rows(),M.cols());
        N = puissance_lente(M,n-1);
        return M*N;
    }
}
MatrixDouble puissance_lente_switch(const MatrixDouble & M, int n){
    switch (n){
        case 0:
            return MatrixDouble::Identity(M.rows(),M.cols());
        case 1:
            return M;
        default:
            MatrixDouble N(M.rows(),M.cols());
            N = puissance_lente_switch(M,n-1);
            return M*N;
    }
}

// question 1.5
/* question 1.6 :
* Cb de multiplications ?
* On pourrait rajouter un cas n==1 pour éviter la multiplication/recurrence sur M*Id*Id */
MatrixDouble puissance_rapide(const MatrixDouble & M, int n){
    if (n==0){  return MatrixDouble::Identity(M.rows(),M.cols()); }
    else if (n%2==0){
        MatrixDouble N(M.rows(),M.cols());
        N = puissance_rapide(M,n/2);
        return N*N;
    } else {
        MatrixDouble N(M.rows(),M.cols());
        N = puissance_rapide(M,(n-1)/2);
        return M*N*N;
    }
}

// question 1.8
Eigen::SparseMatrix<double> puissance_rapide_sparse(Eigen::SparseMatrix<double> & M, int n){
    if (n==0){
        M.setIdentity();
        return M;
    } else if (n%2==0){
        Eigen::SparseMatrix<double> N(M.rows(),M.cols());
        N = puissance_rapide_sparse(M,n/2);
        return N*N;
    } else {
        Eigen::SparseMatrix<double> N(M.rows(),M.cols());
        N = puissance_rapide_sparse(M,(n-1)/2);
        return M*N*N;
    }
}

// question 2.3(12)
auto generate_random_spectrum(mt19937_64 & G, int N){
    normal_distribution<double> Loi_diag(0,1);
    normal_distribution<double> Loi_reste(0,2);
    MatrixDouble M(N,N);

    for(int j=0 ; j<N ; j++){
		// simulation diagonale
		M(j,j) = Loi_diag(G);
        for(int k=j+1 ; k<N ; k++){
            // simulation hors diagonale
            double a_jk = Loi_reste(G);
            M(j,k) = a_jk;
            M(k,j) = a_jk;
        }
    }

    return M;
}


int main(){
    // question 1.3
    MatrixDouble A(3,3);
    A <<    0.4, 0.6, 0.,
            0.75, 0.25, 0.,
            0., 0., 1.;

    cout << "Matrice A :\n" << A << "\n\n";

    int nA = 1000;
    MatrixDouble A_n = puissance_lente(A,nA);
    cout << "Matrice A^" << nA << " (algo lent) :\n" << A_n << "\n\n";

    /* question 1.4 :
    * Pour ne pas créer de copie à chaque appel récursif
    * Sans '&', il y aurait n+1 copies de CHACUN des coefficients de la matrice ?
    * Avec, on ne fait pas de copie, juste une référence à l'emplacement 
    * Pas tant de différences de temps pour les exposants utilisés */

    // question 1.7
    // question 1.8
    ifstream mat("matrice.dat");
    MatrixDouble B_Dense(30,30);
    double coeff;
    int i=0; int j=0;
    while(mat >> coeff){
        B_Dense(i,j) = coeff;
        j++;
        if (j==30){
			i++;
			j=0;
		}
    }    
    int nB = 1000;

    {
    auto t1 = chrono::system_clock::now();
    MatrixDouble B_n_lent = puissance_lente(B_Dense,nB);
    auto t2 = chrono::system_clock::now();
    chrono::duration<double> tps = t2-t1;
    cout << "Calcul de B^" << nB << " (algo lent Dense) en : " << tps.count() << " seconde\n";
	}
	
	{
    auto t1 = chrono::system_clock::now();
    MatrixDouble B_n_rapide = puissance_rapide(B_Dense,nB);
    auto t2 = chrono::system_clock::now();
    chrono::duration<double> tps = t2-t1;
    cout << "Calcul de B^" << nB << " (algo rapide Dense) en : " << tps.count() << " seconde\n";
	}

    // question 1.8
    Eigen::SparseMatrix<double> B_Sparse(30,30);
    i=0; j=0;
    while(mat >> coeff){
        B_Sparse.coeffRef(i,j) = coeff;
        j++;
        if (j==30){
			i++;
			j=0;
		}
    }

    {
    auto t1 = chrono::system_clock::now();
    MatrixDouble B_n_rapide = puissance_rapide(B_Sparse,nB);
    auto t2 = chrono::system_clock::now();
    chrono::duration<double> tps = t2-t1;
    cout << "Calcul de B^" << nB << " (algo rapide Sparse) en : " << tps.count() << " seconde\n\n";
	}

    // **************************************************
    // question 2.1(10)
    int K=20;
    vector<double> hist(K,0);
    int n=20; int N=150;
    int a=-3; int b=3;

    mt19937_64 G(time(NULL));

    for(int i=0 ; i<n ; i++){
        MatrixDouble M = generate_random_spectrum(G,N);
        
        // calcul spectre
        Eigen::EigenSolver<MatrixDouble> Solver(M);
        auto spectrum = Solver.eigenvalues();
        for(auto s : spectrum){
            double vp_norm = s.real()/(2.*sqrt(N));
			int x = floor((vp_norm +(b-a)/2)/(6./K));		// normalisation
			hist[x] += ((vp_norm<b) && (vp_norm>=a)) ? 1./(n*N) : 0;
		}		        
    }

    ofstream histo_f("eigenvalues.dat");
    for(int i=0 ; i<K ; i++){
        histo_f << a+(2*i+1)*(6./K)/2 << "\t" << hist[i] << "\n";
    }
    histo_f.close();

    return 0;
}
