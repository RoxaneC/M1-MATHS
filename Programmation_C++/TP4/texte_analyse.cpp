#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <set>
#include <cmath>

using namespace std;

int main(){
    // question 4.11
    ifstream file_decla("declaration.txt");
    
    map<string, unsigned> S;
    using pair_su = pair<const string, unsigned>;
    
    
    string word;
    while(file_decla >> word){
        S[word]++;
    }
    file_decla.close();

    // question 4.12
    ofstream file("stats.dat");

    //~ for(auto it=S.begin() ; it!=S.end() ; it++){
        //~ file << it->first << " : " << it->second << "\n" ;
    //~ }

    for(pair_su &elem : S){
		file << elem.first << " : " << elem.second << "\n" ;
	}
	file.close();

    // question 4.14
    cout << "1)\tIl y a " << S.size() << " mots différents.\n";
    
    int compteur_mot = count_if(    S.begin(), S.end(),
                                [](const pair_su &p){    return p.first.size()>=7;} );
    cout << "2)\tIl y a " << compteur_mot << " mots différents de 7 lettres ou plus.\n";
    
    auto it = max_element(  S.begin(), S.end(),
                            [](const pair_su &p1, const pair_su &p2){    return p1.second<p2.second; } );
    cout << "3)\tLe mot le plus fréquent est : \'" << it->first << "\', et il apparait " << it->second << " fois.\n";
    
    int compteur_lettre = accumulate(   S.begin(), S.end(), 0,
                                        [](int sum, const pair_su &p){ return sum+ p.first.size()*p.second; } );
    cout << "4)\tIl y a " << compteur_lettre << " lettres au total dans le document.\n";

	set<char> vowels{'a', 'e', 'i', 'o', 'u', 'y'};
	int compt_words_2vow = count_if(	S.begin(), S.end(),
												[vowels](const pair_su &p){ 
													return count_if(	p.first.begin(),p.first.end(),
																		[vowels](const char c){ return vowels.contains(c);} ) == 2;
												}
											);
    cout << "5)\tIl y a " << compt_words_2vow << " mots avec deux voyelles.\n";
    
    //~ string max_e = max_element(	S.begin(), S.end(),
									//~ [](const pair_su &p1, const pair_su &p2){ 
										//~ return count_if(	p1.first.begin(),p1.first.end(),
															//~ [](const char c){ return c=='e';} ) > count_if(	p2.first.begin(),p2.first.end(),
																											//~ [](const char c){ return c=='e';} );
										//~ }
								//~ )->first;
	auto [ elmt_plus_de_e , _ ] = *max_element(	S.begin(), S.end(),
									[](const pair_su &p1, const pair_su &p2){ 
										return 	count_if(	p1.first.begin(),p1.first.end(),
															[](const char c){ return c=='e';} )
													<
												count_if(	p2.first.begin(),p2.first.end(),
															[](const char c){ return c=='e';} );
										}
								);
    cout << "6)\tLe mot \'" << elmt_plus_de_e << "\' contient le plus de fois la lettre \'e\'.\n";
    
    int nb_mot = accumulate(	S.begin(), S.end(), 0,
								[](int sum, const pair_su &p){ return sum+ p.second; } );
    double moy_long = accumulate(	S.begin(), S.end(), 0.,
									[nb_mot](double sum, const pair_su &p){ return sum+ double(p.first.size()*p.second)/nb_mot; } );
	cout << "7.0)\tLongueur moyenne des mots : " << moy_long << "\n";
	double moy_long_carre = accumulate(	S.begin(), S.end(), 0.,
										[nb_mot](double sum, const pair_su &p){ return sum+ double(pow(p.first.size()*p.second,2)) / nb_mot; } );

    double moy_freq = accumulate(	S.begin(), S.end(), 0.,
									[nb_mot](double sum, const pair_su &p){ return sum+ double(p.second)/nb_mot; } );
    double moy_freq_carre = accumulate(	S.begin(), S.end(), 0.,
									[nb_mot](double sum, const pair_su &p){ return sum+ double(pow(p.second,2)) / nb_mot; } );
    
    double moy_long_freq = accumulate(	S.begin(), S.end(), 0.,
									[nb_mot](double sum, const pair_su &p){ return sum+ double(p.first.size()*p.second*p.second)/nb_mot; } );
    
    double cov_long_freq = moy_long_freq - moy_long*moy_freq;    // cov(X,Y) = E[XY] - E[X]E[Y]
	cout << "7.0)\tCovarience entre longueur d'un mot et fréquence du mot : " << cov_long_freq << "\n";

	double sdt_long = sqrt(moy_long_carre - pow(moy_long,2));	// ecart_type = sqrt(E[X^2] - E[X]^2)
	double sdt_freq = sqrt(moy_freq_carre - pow(moy_freq,2)); 	// ecart_type = sqrt(E[X^2] - E[X]^2)
	double corr_long_freq = cov_long_freq/(sdt_long*sdt_freq);	// corr = cov/std1*std2
	cout << "7)\tCorrélation entre longueur d'un mot et fréquence du mot : " << corr_long_freq << "\n";

    return 0;
}

// 2 mots : constitution et organisation (Q15)
// constitutionnellement
