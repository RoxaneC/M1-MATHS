#include <iostream>
#include <fstream>
#include <vector>

int main(){
    int n;
    std::cout << "Entrez un nombre entier <100 :" << std::endl;
    std::cin >> n;
    std::vector<int> tableau1(n);
    std::vector<int> tableau2(n);

    for (int i = 1; i <= n; i++){
        tableau1[i] = i*i;
        tableau2[i] = tableau1[i]*i;
    }

    std::ofstream fichier("donnees.dat");
    fichier << "Voici les carrés et les cubes des entiers :" << std::endl;

    for (int i = n; i > 0; i--){
        fichier << i << " : " << tableau1[i] << ", " << tableau2[i] << std::endl;
    }
    
    fichier.close();
    return 0;
}