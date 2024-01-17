#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Fiche{
    string prenom;
    string ville;
    int age;
    double temps;
};


int main(){
    ifstream fichier("smalldata.txt");
    vector<Fiche> vdata(2500);
    
    string prenom;
    string ville;
    int age;
    double temps;

    while(fichier >> prenom >> ville >> age >> temps;){
        Fiche aux;
        aux.prenom = prenom;
        aux.ville = ville;
        aux.age = age;
        aux.temps = temps;

        vdata.push_back(aux);
    }

    fichier.close();
    return 0;
}
