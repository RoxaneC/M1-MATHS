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
    for(Fiche f : vdata){
        if (f.ville == "Lyon"){
            count1++;
            if (f.age < 30){
                count2++;
            }
        }
    }
    cout << "3.a) Nombre de personnes à Lyon (proportion) : " << count1 << " (" << 100*count1/2500. << "%)" << endl;
    cout << "3.b) ---> de moins de 30ans : " << count2 << endl;

    int countc=0;
    for(Fiche f : vdata){
        if ((f.ville == "Toulouse") && (f.prenom[0] == 'A')){
            countc++;
        }
    }
    cout << "3.c) Un Toulousain dont le prénom commance par \'A\' : " << ((countc > 0) ? "Oui" : "Non") << endl;

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
    cout << "     Âge maximal : " << vdata[ind_max].age << " (" << vdata[ind_max].prenom << ")" << endl;

    double moyenne=0;
    double ecart_type=0;
    for(Fiche f : vdata){
        moyenne += f.age;
        ecart_type += f.age * f.age;
    }
    moyenne /= 2500;
    ecart_type = ecart_type/2500 - moyenne*moyenne;
    cout << "3.e) Âge moyen : " << moyenne << ", écart-type : " << ecart_type << endl;

    int tpsParis, tpsMarseille = 0;
    int countParis, countMarseille = 0;
    for(Fiche f : vdata){
        if (f.ville == "Paris"){
            tpsParis += f.temps;
            countParis++;
        } else if (f.ville == "Marseille"){
            tpsMarseille = f.temps;
            countMarseille++;
        }
    }
    cout << "3.f) Les parisiens en moyenne plus rapide que les Marseillais ? " << ((tpsParis/countParis > tpsMarseille/countMarseille) ? "Oui" : "Non") << endl;

    ofstream fichierT("toulousain.txt");
    for (Fiche f : vdata){
        /* code */
        if (f.ville == "Toulouse"){
            fichierT << f.prenom << " " << f.age << " " << f.temps << endl;
        }
    }
    
    //
    
    fichierdata.close();
    fichierT.close();
    return 0;
}
