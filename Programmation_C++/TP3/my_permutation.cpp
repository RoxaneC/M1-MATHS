#include "my_permutation.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <list>
#include <algorithm>
#include <set>
#include <random>
#include <iterator>

using namespace std;


// question 3.21
long int pgcd(long int a, long int b){
	if (b==0){
		return a;
	} else {
		return pgcd(b, a%b);
	}
};

long int ppcm(long int a, long int b){
	return a*b/pgcd(a,b);
};


// **********************  Définitions pour Permutation  ***********************
// Constructeurs
// question 3.4
Permutation::Permutation(int _n): n(_n), images(_n){
	for(int i=0 ; i<_n ; i++){
		images[i] = i;
	}
};

// question 3.11
Permutation::Permutation(const vector<int> &v): n(v.size()), images(v) {};

// question 3.29
// Référence pour qu'on garde la même seed pour le générateur, plutôt que d'avoir une copie avec nouvelle seed
Permutation::Permutation(int _n, std::mt19937 &g): n(_n), images(_n){
	//
	for(int i=0 ; i<n ; i++)	images[i]=i;
	for(int i=0 ; i<(n-1) ; i++){
		uniform_int_distribution<int> U(i,n-1);
		int rand_j = U(g);
		swap(images[i], images[rand_j]);
	}
};


// Méthodes
// question 3.14
list<int> Permutation::fixed_points() const {
	list<int> list_pt_fix;
	for(int i=0 ; i<n ; i++){
		if (images[i]==i)	list_pt_fix.push_back(i);
	}
	return list_pt_fix;
};

bool Permutation::is_derangement() const {	return fixed_points().empty();};

// question 3.15
Permutation Permutation::inverse() const {
	Permutation perm_res(n);
	for(int i=0; i<n ; i++){
		perm_res.images[images[i]] = i;
	}
	return perm_res;
};

// question 3.18
long int Permutation::order() const {
	list<Cycle> list_cycles = cycles();
	/* long int ord = 1
	for(const Cycle &C : list_cycles){
		ord = ppcm(ord, C.order());
	} */

	long int ord = accumulate(	list_cycles.begin(), list_cycles.end(), long(1),
				[](long int o, const Cycle &C){	return ppcm(o, C.order());});

	return ord;
};

// question 3.20
list<Cycle> Permutation::cycles() const {
	// créer list de cycles vide
	list<Cycle> L;

	// Mettre dans S tous les éléments de 0 à n-1
	set<int> S;
	for(int i=0 ; i<n ; i++){
		S.insert(i);
	}
	
	// Tant que l'ensemble S n'est pas vide...
	while(!S.empty()){
		// on retire le plus petit s
		int s = *(S.begin());
		S.erase(S.begin());

		if( s != images[s] ){
			Cycle C;

			C.add_last_point(s);
			int x = images[s];
			while(x != s) {
				C.add_last_point(x);
				S.erase(find(S.begin(), S.end(), x));
				x = images[x];
			}
			L.push_back(C);
		}
	}
	return L;
};


// Opérateurs
// question 3.5
ostream & operator<<(ostream &o, const Permutation &P){
	o << P.n << " : ";
	for(int k : P.images) {
		o << k << " ";
	}
	return o;
};

// question 3.7
istream & operator>>(std::istream &i, Permutation &P){
	char aux;		// passer après les ':'
	i >> P.n >> aux;
	P.images.resize(P.n);
	for(int & k : P.images){
		i >> k;
	}
	return i;
};

// question 3.13
Permutation operator*(const Permutation &P1, const Permutation &P2){
	int taille1 = P1.n;
	int taille2 = P2.n;

	if (taille1 == taille2){	// si vecteur de la même taille
		Permutation perm_res(taille1);

		for(int i=0 ; i<taille1 ; i++){
			perm_res.images[i] = P1[ P2[i] ];
		}
		return perm_res;

	} else if (taille1 < taille2) {
		Permutation perm_res(taille2);

		for(int i=0 ; i<taille2 ; i++){
			if (i<taille1){
				perm_res.images[i] = P1[ P2[i] ];
			} else {
				perm_res.images[i] = P2[i];
			}
		}
		return perm_res;

	} else {
		Permutation perm_res(taille1);

		for(int i=0 ; i<taille1 ; i++){
			if (i<taille2){
				perm_res.images[i] = P1[ P2[i] ];
			} else {
				perm_res.images[i] = P1[i];
			}
		}
		return perm_res;

	}
};


// ************************  Définitions pour Cycle  *************************
// Opérateurs
// question 3.19
ostream & operator<<(ostream &o, const Cycle &C){
	o << "[ ";
	for(int e : C.elem) {
		o << e << " ";
	}
	o << "]";
	return o;
};

// question 3.24
bool operator<(const Cycle &C1, const Cycle &C2){
	if ( C1.elem.size() == C2.elem.size() ) {
		return lexicographical_compare(C1.elem.begin(), C1.elem.end(), C2.elem.begin(), C2.elem.end());
	} else {
		return C1.elem.size() < C2.elem.size();
	}
};

// question 3.25
vector<int>::iterator Cycle::find(int i) const{
	//
};

// question 3.37
Cycle Cycle::inverse() const {
	Cycle C;
	for(int i=elem.size(); i>0 ; i--){
		C.add_last_point(elem[i]);
	}
	return C;
};



// ********************************  Main  ***********************************
int main(){
	// question 3.6
	Permutation b(6);
	cout << "b >> " << b << "\n";
	
	// question 3.7
	Permutation perm_test_in;
	ifstream f_in("file_s.dat");
	f_in >> perm_test_in;
	f_in.close();
	
	ofstream f_out("test_file_s.dat");
	f_out << perm_test_in;
	f_out.close();
	
	// question 3.11
	vector<int> v{2,4,5,3,1,0};
	Permutation a(v);
	cout << "a >> " << a << "\n";
	
	// question 3.12 : pourquoi pas ?
	
	// test question 3.13
	for(int i=0; i<=6; ++i) {
		std::cout << "a^" << i << "\nb >> " << b << "\n";
		b = b*a;
	}

	// test question 3.14
	list<int> fp = a.fixed_points();
	for_each(	fp.begin(), fp.end(),
				[](const int & pt){ cout << pt << " ";} );
	cout << ": indices des points fixes\n";

	// test question 3.15
	cout << "\nPermutation d'origine : " << a << "\n";
	cout << "Permutation inverse : " << a.inverse() << "\n";
	cout << "Permutation inverse de l'inverse : " << a.inverse().inverse() << "\n\n";

	// ******* Deuxieme partie: un peu plus d'algorithmique
	// lecture de deux permutations dans deux fichiers
    std::ifstream fichier_s("./file_s.dat");
    std::ifstream fichier_t("./file_t.dat");
    Permutation s,t;
    fichier_s >> s;
    fichier_t >> t;
    fichier_s.close();
    fichier_t.close();
    
	// Calcul test de cycles
	list<Cycle> la = a.cycles();
	cout << "Les cycles de a sont : ";
	for(const auto &c : la)		cout << c << " ; ";
	cout << "\nL'ordre de la permutaiton a est égale à " << a.order() << "\n";
	cout << "Inverse du premier cycle de a : " << (*(la.begin())).inverse() << "\n\n";

	// Calcul de u=s * t^{-1} et son ordre
    Permutation u = s*t.inverse();
	list<Cycle> lu = u.cycles();
	cout << "Les ordres des cycles de u sont : ";
	for(const auto &c : lu)		cout << c.order() << " ; ";
    cout << "\nL'ordre de la permutation s*t^-1 est égal à " << u.order() << "\n";
    
    /* RESULTAT -7542714631..... !!!!
    * parce que l'ordre est trop grand, donc OOB
    * Solution ? pas vraiment, ne fonctionne que pour les "petites" permutations;
    * ou bibliothèque spécifique pour coder avec bcp de RAM
    * parce que les cycles de u sont de longueurs :
    * --> 11_307 , 1_739 , 1_254 , 1_049 , 26 , 153 , 682 , 79 , 30 , 3 , 51 , 8 , 3 */
        
	// Extraction des cycles de u
    cout << "Cette permutation a " << lu.size() <<
        " cycles, dont le plus grand a pour longueur " <<
        max_element(lu.begin(), lu.end())->order() << "\n\n";
        //attention, cela utilise < sur des Cycle !

	// ******* Troisieme partie: génération aléatoire et Monte-Carlo
	// question 3.30
    std::mt19937 g(time(nullptr));
    unsigned n=100;
    unsigned nb_echant = 10000;
    unsigned nb_derang = 0;
    for(unsigned i = 0; i < nb_echant; ++i) {
        nb_derang += Permutation(n,g).is_derangement();
    }
    std::cout << "La proportion de dérangements est environ "
        << nb_derang/double(nb_echant) << "\n";

	return 0;
}
