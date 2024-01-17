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
bool question_3c(vector<Fiche> v){
    int count = 0;
    bool existe;
    for(int i=0; i<2500 ; i++){
        if ((v[i].ville == "Toulouse") && (v[i].prenom[0] == 'A')){
            count++;
        }
    }
    existe = (count > 0) ? true : false;
    return count;
}


//
int main(){
    ifstream fichierdata("smalldata.txt");

    // question 2
    /* vector<Fiche> vdata(2500);
    for(int i=0; i<2500 ; i++){
        Fiche aux;
        fichier >> aux.prenom >> aux.ville >> aux.age >> aux.temps;

        vdata[i] = aux;
    } */

    // question 4
    vector<Fiche> vdata;
    string prenom;
    string ville;
    int age;
    double temps;
    while(fichierdata >> prenom >> ville >> age >> temps){
        Fiche aux;
        aux.prenom = prenom;
        aux.ville = ville;
        aux.age = age;
        aux.temps = temps;

        vdata.push_back(aux);
    }

    // question 3
    int count1 = 0;
    int count2 = 0;
    for(int i=0; i<2500 ; i++){
        if (vdata[i].ville == "Lyon"){
            count1++;
            if (vdata[i].age < 30){
                count2++;
            }
        }
    }
    cout << "3.a) Nombre de personnes à Lyon (proportion) : " << count1 << " (" << 100*count1/2500 << "%)" << endl;
    cout << "3.b) ---> de moins de 30ans : " << count2 << endl;
    cout << "3.c) Un Toulousain dont le prénom commance par \'A\' : " << question_3c(vdata) << endl;

    int ind_min = 0;
    int ind_max = 0;
    for(int i=1; i<2500 ; i++){
        if (vdata[i].age < vdata[ind_min].age){
            ind_min=i;
        } else if (vdata[i].age > vdata[ind_max].age){
            ind_max=i;
        }
    }
    cout << "3.d) Âge minimal : " << vdata[ind_min].age << " (" << vdata[ind_min].prenom << ")" << endl;
    cout << "   Âge maximal : " << vdata[ind_max].age << " (" << vdata[ind_max].prenom << ")" << endl;

    double moyenne=0;
    double ecart_type=0;
    for(int i=0; i<2500 ; i++){
        moyenne += vdata[i].age;
        ecart_type += vdata[i].age * vdata[i].age;
    }
    moyenne /= 2500;
    ecart_type = ecart_type/2500 - moyenne*moyenne;
    cout << "3.e) Âge moyen : " << moyenne << ", écart-type : " << ecart_type << endl;

    int tpsParis, tpsMarseille = 0;
    int countParis, countMarseille = 0;
    for(int i=1; i<2500 ; i++){
        if (vdata[i].ville == "Paris"){
            tpsParis += vdata[i].temps;
            countParis++;
        } else if (vdata[i].ville == "Marseille"){
            tpsMarseille = vdata[i].temps;
            countMarseille++;
        }
    }
    cout << "3.f) Les parisiens en moyenne plus rapide que les Marseillais ? " << ((tpsParis/countParis > tpsMarseille/countMarseille) ? "Oui" : "Non") << endl;

    ofstream fichierT("toulousain.txt");
    fichierT << "3.f)" << endl;
    for (int i=0; i<2500 ; i++){
        /* code */
        if (vdata[i].ville == "Toulouse"){
            fichierT << vdata[i].prenom << " " << vdata[i].age << " " << vdata[i].temps << endl;
        }
    }
    
    //
    
    fichierdata.close();
    fichierT.close();
    return 0;
}
