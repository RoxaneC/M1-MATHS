#include <Eigen/Dense> // mettre '-I /usr/include/eigen3/' à la compilation !!!
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;
typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> MatrixDouble;

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


int main(){
    // question 1.3
    MatrixDouble A(3,3);
    A <<    0.4, 0.6, 0.,
            0.75, 0.25, 0.,
            0., 0., 1.;

    cout << "Matrice A :\n" << A << "\n\n";

    int nA = 1000;
    MatrixDouble A_n = puissance_lente(A,nA);
    cout << "Matrice A^" << nA << " :\n" << A_n << "\n\n";

    /* question 1.4 :
    * Pour ne pas créer de copie à chaque appel récursif
    * Sans '&', il y aurait n+1 copies de CHACUN des coefficients de la matrice ?
    * Avec, on ne fait pas de copie, juste une référence à l'emplacement 
    * Pas tant de différences de temps pour les exposants utilisés */

    // question 1.7
    ifstream mat("matrice.dat");
    MatrixDouble B(30,30);
    int coeff;
    int i=0; int j=0;
    while(mat >> coeff){
        B(i,j) = coeff;
        j++;
        if (j==30){
			i++;
			j=0;
		}
    }
    cout << "Matrice B :\n" << B << "\n\n";
    
    int nB = 1000;
    {
    auto t1 = chrono::system_clock::now();
    MatrixDouble B_n_lent = puissance_lente(B,nB);
    auto t2 = chrono::system_clock::now();
    chrono::duration<double> tps = t2-t1;
    cout << "Calcul de B^" << nB << " (algo lent) en : " << tps.count() << "\n";
	}
	
	{
    auto t1 = chrono::system_clock::now();
    MatrixDouble B_n_rapide = puissance_rapide(B,nB);
    auto t2 = chrono::system_clock::now();
    chrono::duration<double> tps = t2-t1;
    cout << "Calcul de B^" << nB << " (algo rapide) en : " << tps.count() << "\n";
	}

    return 0;
}
