#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <numeric>

using namespace std;

int main(){
    // question 4.11
    ifstream file_decla("declaration.txt");
    map<string, unsigned> S;
    string word;
    while(file_decla >> word){
        S[word]++;
    }
    file_decla.close();

    // question 4.12
    ofstream file("stats.dat");

    for(auto it=S.begin() ; it!=S.end() ; it++){
        file << it->first << " : " << it->second << "\n" ;
    }

    // question 4.14
    cout << "1)\tIl y a " << S.size() << " mots différents.\n";
    int compteur_mot = count_if(    S.begin(), S.end(),
                                [](const pair<string, unsigned> &p){    return p.first.size()>=7;} );
    cout << "2)\tIl y a " << compteur_mot << " mots différents de 7 lettres ou plus.\n";
    auto it = max_element(  S.begin(), S.end(),
                            [](const pair<string, unsigned> &p1, const pair<string, unsigned> &p2){    return p1.second<p2.second; } );
    cout << "3)\tLe mot le plus fréquent est : " << it->first << ", et il apparait " << it->second << " fois.\n";
    int compteur_lettre = accumulate(   S.begin(), S.end(), 0,
                                        [](int sum, const pair<string, unsigned> &p){ return sum+ p.first.size()*p.second; } );
    cout << "4)\tIl y a " << compteur_lettre << " lettres au total dans le document.\n";


    return 0;
}

// 2 mots : constitution et organisation
// longue moyenne 5,0774...
// constitutionnellement