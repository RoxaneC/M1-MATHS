#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <set>
#include <cmath>
#include <tuple>

using namespace std;
using pair_su = pair<const string, unsigned>;

tuple<double, unsigned /* , vector<string> */ > basic_statistics(const map<string,unsigned> &M){
    int nb_mot = accumulate(	M.begin(), M.end(), 0,
								[](int sum, const pair_su &p){ return sum+ p.second; } );
    double moy_long = accumulate(	M.begin(), M.end(), 0.,
									[nb_mot](double sum, const pair_su &p){ return sum+ double(p.first.size()*p.second)/nb_mot; } );

    unsigned size_longest_word = max_element(  M.begin(), M.end(),
                                                [](const pair_su &p1, const pair_su &p2){    return p1.first.size()<p2.first.size(); } )->first.size();

    auto T=make_tuple(moy_long, size_longest_word);
    return T;
};

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
										[nb_mot](double sum, const pair_su &p){ return sum+ double(p.first.size()*p.second*p.first.size()*p.second) / nb_mot; } );

    double moy_freq = accumulate(	S.begin(), S.end(), 0.,
									[nb_mot](double sum, const pair_su &p){ return sum+ double(p.second)/nb_mot; } );
    double moy_freq_carre = accumulate(	S.begin(), S.end(), 0.,
									[nb_mot](double sum, const pair_su &p){ return sum+ double(p.second*p.second) / nb_mot; } );
    
    double moy_long_freq = accumulate(	S.begin(), S.end(), 0.,
									[nb_mot](double sum, const pair_su &p){ return sum+ double(p.first.size()*p.second*p.second)/nb_mot; } );
    
    double cov_long_freq = moy_long_freq - moy_long*moy_freq;       // cov(X,Y) = E[XY] - E[X]E[Y]
	cout << "7.0)\tCovarience entre longueur d'un mot et fréquence du mot : " << cov_long_freq << "\n";

	double sdt_long = sqrt(moy_long_carre - moy_long*moy_long);     // ecart_type = sqrt(E[X^2] - E[X]^2)
	double sdt_freq = sqrt(moy_freq_carre - moy_freq*moy_freq);     // ecart_type = sqrt(E[X^2] - E[X]^2)
	double corr_long_freq = cov_long_freq/(sdt_long*sdt_freq);      // corr = cov/std1*std2
	cout << "7)\tCorrélation entre longueur d'un mot et fréquence du mot : " << corr_long_freq << "\n";

    // question 4.15
    auto more_12_letters = [](const string &s){ return s.size()>=12; };
    auto more_13_time = [](const int i){    return i>=13; };
    auto no_letter_e = [](const string &s){ return !s.contains('e'); };     // c++23
    auto last_letter_s = [](const string &s){   return s.back()!='s'; };

    cout << "Question 4.15 :\t";
    for(pair_su &elem : S){
        if (more_12_letters(elem.first)
                && more_13_time(elem.second)
                && no_letter_e(elem.first)
                && last_letter_s(elem.first))
            cout << elem.first << ", ";
    }
    cout << "\n";

    // question 4.18
    double x; unsigned n;
    auto T = basic_statistics(S);
    tie(x,n) = T;
    cout << "Question 4.18 :\tTuple ( long. moy. : " << x << " , size mot long : " << n << " )\n";

    return 0;
}

// constitutionnellement