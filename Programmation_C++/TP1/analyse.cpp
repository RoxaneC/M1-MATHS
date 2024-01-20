#include <iostream>
#include <fstream>

#include <vector>
#include <string>

#include <algorithm>

using namespace std;
struct Fiche{
    string prenom;
    string ville;
    int age;
    double temps;
};
//

// version alternative question 1.4
vector<Fiche> initialisation(string nomFichier){

    ifstream fichierdata(nomFichier);
    vector<string> data;
    string ligne;

    while (getline(fichierdata,ligne)) {
        /* récupère les lignes dans un vecteur */
        data.push_back(ligne);
    }


    // Création des fiches
    vector<Fiche> vfiche;

    for (string s : data){
        /* pour chaque string du vecteur data */
        vector<string> subs;

        size_t pos = s.find("\t", 0);   // première position
        string sub = s.substr(0,pos);     // tire la substring avant la première tabulation
        subs.push_back(sub);

        // check les autres tabulations
        while(pos != string::npos){
            size_t pos2 = s.find("\t",pos+1);     // trouve la prochaine tabulation

            sub = s.substr(pos+1,pos2-pos-1);     // tire la substring entre les deux tabulations
            subs.push_back(sub);        // ajoute aux vecteurs des substring de l'itération
            pos=pos2;
        }

        // crée la fiche auxiliaire
        Fiche f_aux;
        f_aux.prenom = subs[0];
        f_aux.ville = subs[1];
        f_aux.age = stoi(subs[2]);
        f_aux.temps = stod(subs[3]);
        vfiche.push_back(f_aux);    // ajout de la fiche au vecteur
    }

    fichierdata.close();
    return vfiche;
}


// *******************
int main(){
    // question 1.2

    /* ifstream fichierdata("smalldata.txt");
    vector<Fiche> vdata(2500);
    for(int i=0; i<2500 ; i++){
        Fiche aux;
        fichier >> aux.prenom >> aux.ville >> aux.age >> aux.temps;

        vdata[i] = aux;
    } */


    // question 1.4
    string prenom;
    string ville;
    int age;
    double temps;
    /* ifstream fichierdata("smalldata.txt");
    vector<Fiche> vdata;
    while(fichierdata >> prenom >> ville >> age >> temps){
        Fiche aux;
        aux.prenom = prenom;
        aux.ville = ville;
        aux.age = age;
        aux.temps = temps;

        vdata.push_back(aux);
    } */

    // question 1.4 autre version
    vector<Fiche> vdata;
    vdata = initialisation("smalldata.txt");



    // **************************************************
    // question 1.3
    cout << "Sans <algorithm>" << endl;
    int countLyon = 0;
    int count30 = 0;
    for(Fiche f : vdata){
        if (f.ville == "Lyon"){
            countLyon++;
            if (f.age < 30){
                count30++;
            }
        }
    }
    cout << "1.3.a) Nombre de personnes à Lyon (proportion) : " << countLyon << " (" << 100*countLyon/2500. << "%)" << endl;
    cout << "1.3.b) ---> de moins de 30ans : " << count30 << endl;

    int countA=0;
    for(Fiche f : vdata){
        if ((f.ville == "Toulouse") && (f.prenom[0] == 'A')){
            countA++;
        }
    }
    cout << "1.3.c) Un Toulousain dont le prénom commance par \'A\' : " << ((countA > 0) ? "Oui" : "Non") << endl;

    int ind_min = 0;
    int ind_max = 0;
    for(int i=1; i<2500 ; i++){
        if (vdata[i].age < vdata[ind_min].age){
            ind_min=i;
        } else if (vdata[i].age > vdata[ind_max].age){
            ind_max=i;
        }
    }
    cout << "1.3.d) Âge minimal : " << vdata[ind_min].age << " (" << vdata[ind_min].prenom << ")" << endl;
    cout << "       Âge maximal : " << vdata[ind_max].age << " (" << vdata[ind_max].prenom << ")" << endl;

    double moyenne=0.;
    double ecart_type=0.;
    for(Fiche f : vdata){
        moyenne += f.age;
        ecart_type += f.age * f.age;
    }
    moyenne /= 2500;
    ecart_type = ecart_type/2500 - moyenne*moyenne;
    cout << "1.3.e) Âge moyen : " << moyenne << ", écart-type : " << ecart_type << endl;

    int tpsParis, tpsMarseille = 0;
    double countParis, countMarseille = 0.;
    for(Fiche f : vdata){
        if (f.ville == "Paris"){
            tpsParis += f.temps;
            countParis++;
        } else if (f.ville == "Marseille"){
            tpsMarseille = f.temps;
            countMarseille++;
        }
    }
    cout << "1.3.f) Les parisiens en moyenne plus rapide que les Marseillais ? " << ((tpsParis/countParis > tpsMarseille/countMarseille) ? "Oui" : "Non") << endl;

    // question 3.g)
    ofstream fichierT("toulousain.txt");
    for (Fiche f : vdata){
        if (f.ville == "Toulouse"){
            fichierT << f.prenom << " " << f.age << " " << f.temps << endl;
        }
    }
    

    // **************************************************
    // question 2.1
    cout << "Avec <algorithm>" << endl;
    int nb_Lyon = count_if( vdata.begin(), vdata.end(),
                            [](Fiche f){    return (f.ville == "Lyon");} );
    int nb_Lyon30 = count_if(   vdata.begin(), vdata.end(),
                                [](Fiche f){    return ((f.ville == "Lyon") && (f.age < 30));} );
    cout << "2.3.a) Nombre de personnes à Lyon (proportion) : " << nb_Lyon << " (" << 100*nb_Lyon/2500. << "%)" << endl;
    cout << "2.3.b) ---> de moins de 30ans : " << nb_Lyon30 << endl;

    bool is_TA = any_of(    vdata.begin(), vdata.end(),
                            [](Fiche f){    return ((f.ville == "Toulouse") && (f.prenom[0]=='A'));} );
    cout << "2.3.c) Un Toulousain dont le prénom commance par \'A\' : " << (is_TA ? "Oui" : "Non") << endl;


    //cout << "1.3.e) Âge moyen : " << moyenne << ", écart-type : " << ecart_type << endl;


    fichierT.close();
    return 0;
}
