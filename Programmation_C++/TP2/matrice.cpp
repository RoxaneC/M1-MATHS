#include <Eigen/Dense> // installer en rentrant !!!

using namespace std;
typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> MatrixDouble;

// question 1.1
// question 1.2 : pour éviter l'opération M*Id
MatrixDouble puissance_lente(const MatrixDouble & M, int n){
    if (n==0){  return MatrixDouble::Identity(M.size(),M.size()); }
    else if (n==1){ return M; }
    else {
        MatrixDouble N(M.size(),M.size());
        N = puissance_lente(M,n-1);
        return M*N;
    }
}
MatrixDouble puissance_lente_switch(const MatrixDouble & M, int n){
    switch (n){
        case 0:
            return MatrixDouble::Identity(M.size(),M.size());
        case 1:
            return M;
        default:
            MatrixDouble N(M.size(),M.size());
            N = puissance_lente_switch(M,n-1);
            return M*N;
    }
}

// question 1.5
// question 1.6 : ...
MatrixDouble puissance_rapide(const MatrixDouble & M, int n){
    if (n==0){  return MatrixDouble::Identity(M.size(),M.size()); }
    else if (n%2==0){
        MatrixDouble N(M.size(),M.size());
        N = puissance_rapide(M,n/2);
        return N*N;
    } else {
        MatrixDouble N(M.size(),M.size());
        N = puissance_rapide(M,(n-1)/2);
        return M*N*N;
    }
}


int main(){
    // question 1.3
    MatrixDouble A(3,3);
    A = {0.4, 0.6, 0., 0.75, 0.25, 0., 0., 0., 1.};

    int n = 100;
    MatrixDouble A_n = puissance_lente(A,n);
    // question 1.4 : pour ne pas créer de copie à chaque appel récursif

    // question 1.7

    return 0;
}