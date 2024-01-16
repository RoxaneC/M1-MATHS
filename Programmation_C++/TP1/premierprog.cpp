#include <iostream>
#include <cmath>

double aire_du_cercle(double x){
    return M_PI*x*x;
}

double aire_du_carre(double x){
    return x*x;
}

int main(){
    double r;
    std::cout << "Entrez le rayon du cercle :" << std::endl;
    std::cin >> r;
    std::cout << "Son aire est " << aire_du_cercle(r) << std::endl;

    double l;
    std::cout << "Entrez la longueur du côté :" << std::endl;
    std::cin >> l;
    std::cout << "Son aire est " << aire_du_carre(l) << std::endl;
    return 0;
}