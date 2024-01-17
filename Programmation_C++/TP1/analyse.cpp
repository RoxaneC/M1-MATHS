#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
struct Fiche{
    string prenom;
    string ville;
    int age;
    double temps;
};

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
    cout << "a) Nombre de personnes à Lyon (proportion) : " << question_3a(vdata) << " (" << 100*count/2500 << "%)" << endl;
    cout << "b) ---> de moins de 30ans : " << question_3b(vdata) << endl;
    cout << "c) Un Toulousain dont le prénom commance par \'A\' : " << question_3c(vdata) << endl;

    int ind_min = 0;
    int ind_max = 0;
    for(int i=1; i<2500 ; i++){
        if (v[i].age < v[ind_min].age){
            ind_min=i;
        } else if (v[i].age > v[ind_max].age){
            ind_max=i;
        }
    }
    cout << "d) Âge minimal : " << vdata[inf_min].age << " (" vdata[inf_min].prenom << ")" << endl;
    cout << "   Âge maximal : " << vdata[ind_max].age << " (" vdata[ind_max].prenom << ")" << endl;

    double moyenne=0;
    double ecart_type=0;
    for(int i=0; i<2500 ; i++){
        moyenne += v[i].age;
        ecart_type += v[i].age * v[i].age;
    }
    moyenne /= 2500;
    ecart_type = ecart_type/2500 - moyenne*moyenne;
    cout << "e) Âge moyen : " << moyenne << ", écart-type : " << ecart_type << endl;

    //
    
    fichier.close();
    return 0;
}
