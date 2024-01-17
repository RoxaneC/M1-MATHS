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

    fichier.close();
    return 0;
}