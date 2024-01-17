#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
//
struct Fiche{
    string prenom;
    string ville;
    int age;
    double temps;
};
//
// question 3
int question_3a(vector<Fiche> v){
    int count = 0;
    for(int i=0; i<2500 ; i++){
        if (v[i].ville == "Lyon"){
            count++;
        }
    }
    return count;
}

int question_3b(vector<Fiche> v){
    int count = 0;
    for(int i=0; i<2500 ; i++){
        if (v[i].ville == "Lyon") && (v[i].age < 30){
            count++;
        }
    }
    return count;
}

bool question_3c(vector<Fiche> v){
    int count = 0;
    bool existe;
    for(int i=0; i<2500 ; i++){
        if (v[i].ville == "Toulouse") && (v[i].prenom[0] == 'A'){
            count++;
        }
    }
    existe = (count > 0) ? true ; false;
    return count;
}

//
int main(){
    ifstream fichier("smalldata.txt");
    // vector<Fiche> vdata(2500);
    vector<Fiche> vdata;

    // question 2
    string prenom;
    string ville;
    int age;
    double temps;
    while(fichier >> prenom >> ville >> age >> temps){
        Fiche aux;
        aux.prenom = prenom;
        aux.ville = ville;
        aux.age = age;
        aux.temps = temps;

        vdata.push_back(aux);
    }

    // question 3
    cout << "Nombre de personnes à Lyon : " << question_3a(vdata) << " (" << 100*count/2500 << "%)" << endl;
    cout << "---> de moins de 30ans : " << question_3b(vdata) << endl;
    cout << "Un Toulousain dont le prénom commance par \'A\' " << question_3c(vdata) << endl;

    fichier.close();
    return 0;
}
