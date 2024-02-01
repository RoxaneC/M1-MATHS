#include <iostream>
#include <fstream>

#include <vector>
#include <set>
#include <cmath>
#include <string>

#include <algorithm>
#include <numeric>
#include <iterator>
#include <map>

using namespace std;

struct Fiche{
    string prenom;
    string ville;
    int age;
    double temps;
};

// *******************
// version alternative question 1.4
vector<Fiche> initialisation(string nomFichier){

    ifstream fichierdata(nomFichier);
    vector<string> data;
    string ligne;

    while (getline(fichierdata,ligne)) {
        /* récupère les lignes dans un vecteur */
        data.push_back(ligne);
    }
    fichierdata.close();


    // Création des fiches
    vector<Fiche> vfiche;

    for (string s : data){
        /* pour chaque string du vecteur data */
        vector<string> subs;

        size_t pos = s.find("\t", 0);   // première position d'une tabulation
        string sub = s.substr(0,pos);     // tire la substring avant la première tabulation
        subs.push_back(sub);

        // check les autres tabulations
        while(pos != string::npos){
            size_t pos2 = s.find("\t",pos+1);     // trouve la prochaine tabulation

            sub = s.substr(pos+1,pos2-(pos+1));     // tire la substring entre les deux tabulations
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

    return vfiche;
}


// *******************
int main(){
	int N = 2500;

    // question 1.2
    /* ifstream fichierdata("smalldata.txt");
    vector<Fiche> vdata(N);
    for(int i=0; i<N ; i++){
        Fiche aux;
        fichier >> aux.prenom >> aux.ville >> aux.age >> aux.temps;

        vdata[i] = aux;
    } */


    // question 1.4
    string prenom;
    string ville;
    int age;
    double temps;
    ifstream fichierdata("smalldata.txt");
    vector<Fiche> vdata;
    while(fichierdata >> prenom >> ville >> age >> temps){
        Fiche aux;
        aux.prenom = prenom;
        aux.ville = ville;
        aux.age = age;
        aux.temps = temps;

        vdata.push_back(aux);
    }

    // question 1.4 autre version
    // Erreur de segmentation ! Pas sur les ordi de la fac o_O?
    /* vector<Fiche> vdata;
    vdata = initialisation("smalldata.txt"); */



    // **************************************************
    // question 1.3
    cout << "Sans <algorithm>\n";
    int countLyon = 0;
    int count30 = 0;
    for(const Fiche & f : vdata){
        if (f.ville == "Lyon"){
            countLyon++;
            if (f.age < 30){
                count30++;
            }
        }
    }
    cout    << "1.3.a) Nombre de personnes à Lyon (proportion) : " << countLyon
            << " (" << 100*double(countLyon)/N << "%)\n";
    cout << "1.3.b) ---> de moins de 30ans : " << count30 << "\n";

    int countA=0;
    vector<string> prenoms;
    for(const Fiche & f : vdata){
        if ((f.ville == "Toulouse") && (f.prenom.front() == 'A')){
            countA++;
            prenoms.push_back(f.prenom);
        }
    }
    cout << "1.3.c) Un Toulousain dont le prénom commance par \'A\' : " << ((countA > 0) ? "Oui\n" : "Non\n");
    cout << "---> il y en a " << countA << " et le premier s'appelle " << prenoms.front() << "\n";

    int ind_min = 0;
    int ind_max = 0;
    for(int i=1; i<N ; i++){
        if (vdata[i].age < vdata[ind_min].age){
            ind_min=i;
        } else if (vdata[i].age > vdata[ind_max].age){
            ind_max=i;
        }
    }
    cout << "1.3.d) Âge minimal : " << vdata[ind_min].age << " (" << vdata[ind_min].prenom << ")\n";
    cout << "       Âge maximal : " << vdata[ind_max].age << " (" << vdata[ind_max].prenom << ")\n";

    double moyenne=0.;
    double ecart_type=0.;
    for(const Fiche & f : vdata){
        moyenne += f.age;
        ecart_type += f.age * f.age;
    }
    moyenne /= N;
    ecart_type = sqrt(ecart_type/N - moyenne*moyenne);
    cout << "1.3.e) Âge moyen : " << moyenne << ", écart-type : " << ecart_type << "\n";

    double tpsParis=0., tpsMarseille=0.;
    int countParis=0, countMarseille=0;
    for(const Fiche & f : vdata){
        if (f.ville == "Paris"){
            tpsParis += f.temps;
            countParis++;
        } else if (f.ville == "Marseille"){
            tpsMarseille += f.temps;
            countMarseille++;
        }
    }
    cout	<< "1.3.f) Les Parisiens en moyenne plus rapide que les Marseillais ? "
            << ((tpsParis/countParis > tpsMarseille/countMarseille) ? "Oui" : "Non") << "\n";
    cout << "---> Paris : " << tpsParis/countParis << "\n---> Marseille : " << tpsMarseille/countMarseille << "\n";

    // question 3.g)
    vector<Fiche> ficheT;
    int compt=0;
    ofstream fichierT("toulousain.txt");
    for (const Fiche & f : vdata){
        if (f.ville == "Toulouse"){
	        compt++;
	        
            Fiche aux;
            aux.prenom = f.prenom;
            aux.ville = f.ville;
            aux.age = f.age;
            aux.temps = f.temps;

            ficheT.push_back(aux);
            fichierT << f.prenom << "\t" << f.ville << "\t" << 2018-f.age << "\t" << f.temps << "\n";
        }
    }
    fichierT.close();
    
    int ageT=0;
    double tempsT=0.;
    double agetempsT=0.;
    for(const Fiche & f : ficheT){
        ageT += f.age;
        tempsT += f.temps;
        agetempsT += f.age*f.temps;
    }
    double covAgeTempsT = agetempsT/compt - (double(ageT)/compt)*(tempsT/compt);    // cov(X,Y) = E[XY] - E[X]E[Y]
    cout << "1.3.h) Covariance empirique entre âge et temps au 100 mètres pour les Toulousains : " << covAgeTempsT << "\n";

    set<string> villes;
    for(const Fiche & f : vdata){
		villes.insert(f.ville);
	}
	cout << "1.3.i) Liste des villes présentes (avec set) :\n";
	for(string s : villes){
		cout << "- " << s << "\n";
	}


    // **************************************************
    // question 2.1
    cout << endl << "Avec <algorithm>\n";
    int nb_Lyon = count_if( vdata.begin(), vdata.end(),
                            [](const Fiche & f){    return (f.ville == "Lyon");} );
    int nb_Lyon30 = count_if(   vdata.begin(), vdata.end(),
                                [](const Fiche & f){    return ((f.ville == "Lyon") && (f.age < 30));} );
    cout << "2.1.a) Nombre de personnes à Lyon (proportion) : " << nb_Lyon << " (" << 100*double(nb_Lyon)/N << "%)\n";
    cout << "2.1.b) ---> de moins de 30ans : " << nb_Lyon30 << "\n";

    bool is_TA = any_of(    vdata.begin(), vdata.end(),
                            [](const Fiche & f){    return ((f.ville == "Toulouse") && (f.prenom.front()=='A'));} );
    cout << "2.1.c) Un Toulousain dont le prénom commance par \'A\' : " << (is_TA ? "Oui\n" : "Non\n");

    auto minmax = minmax_element(   vdata.begin(), vdata.end(),
                                    [](const Fiche & f1, const Fiche & f2){ return f1.age < f2.age;} );
    cout << "2.1.d)	Âge minimal : " << minmax.first->age << " (" << minmax.first->prenom << ")\n";
    cout << "       Âge maximal : " << minmax.second->age << " (" << minmax.second->prenom << ")\n";
    /* Autre méthode pour les pointeurs !
    cout << "2.1.d)	Âge minimal : " << (*minmax.first).age << " (" << (*minmax.first).prenom << ")" << endl;
    cout << "       Âge maximal : " << (*minmax.second).age << " (" << (*minmax.second).prenom << ")" << endl; */
    
    double moy_age = accumulate(	vdata.begin(), vdata.end(), 0.,
									[N](double sum, const Fiche & f){	return sum + double(f.age)/N;} );
    double moy_age_carre = accumulate(	vdata.begin(), vdata.end(), 0.,
										[N](double sum, const Fiche & f){	return sum + double(f.age*f.age)/N;} );
    double ecart_age = sqrt(moy_age_carre - moy_age*moy_age);
    cout << "2.1.e) Âge moyen : " << moy_age << ", écart-type : " << ecart_age << endl;

    double temps_Paris = accumulate(	vdata.begin(), vdata.end(), 0.,
									    [](double sum, const Fiche & f){	return (f.ville == "Paris") ? sum + f.temps : sum;} );
    double temps_Marseille = accumulate(	vdata.begin(), vdata.end(), 0.,
										    [](double sum, const Fiche & f){	return (f.ville == "Marseille") ? sum + f.temps : sum;} );
    int nb_Paris = count_if(	vdata.begin(), vdata.end(),
								[](const Fiche & f){    return (f.ville == "Paris");} );
    int nb_Marseille = count_if(	vdata.begin(), vdata.end(),
									[](const Fiche & f){    return (f.ville == "Marseille");} );
    cout    << "2.1.f) Les Parisiens en moyenne plus rapide que les Marseillais ? "
            << ((temps_Paris/nb_Paris > temps_Marseille/nb_Marseille) ? "Oui\n" : "Non\n");
    cout << "---> Paris : " << temps_Paris/nb_Paris << "\n---> Marseille : " << temps_Marseille/nb_Marseille << "\n";
    
    ofstream fichierT2("toulousain_algo.txt");
    for_each(   vdata.begin(), vdata.end(),
                [& fichierT2](const Fiche & f){    if (f.ville == "Toulouse") fichierT2 << f.prenom << "\t" << f.ville << "\t" << 2018-f.age << "\t" << f.temps << "\n";} );
    fichierT2.close();

    int nb_Toulouse = count_if(	vdata.begin(), vdata.end(),
								[](const Fiche & f){    return (f.ville == "Toulouse");} );
    double moy_temps_Toulouse = accumulate(	vdata.begin(), vdata.end(), 0.,
										    [nb_Toulouse](double sum, const Fiche & f){	return (f.ville == "Toulouse") ? sum + f.temps/nb_Toulouse: sum;} );
    double moy_age_Toulouse = accumulate(	vdata.begin(), vdata.end(), 0.,
										    [nb_Toulouse](double sum, const Fiche & f){	return (f.ville == "Toulouse") ? sum + double(f.age)/nb_Toulouse : sum;} );
    double moy_agetemps_Toulouse = accumulate(	vdata.begin(), vdata.end(), 0.,
										        [nb_Toulouse](double sum, const Fiche & f){	return (f.ville == "Toulouse") ? sum + f.temps*f.age/nb_Toulouse : sum;} );
    double cov_agetemps_Toulouse = moy_agetemps_Toulouse - moy_temps_Toulouse*moy_age_Toulouse;    // cov(X,Y) = E[XY] - E[X]E[Y]
    cout << "2.1.h) Covariance empirique entre âge et temps au 100 mètres pour les Toulousains : " << cov_agetemps_Toulouse << "\n";

    set<string> liste_villes;
    transform(	vdata.begin(), vdata.end(), inserter(liste_villes,liste_villes.end()),
				[](const Fiche & f) { return f.ville; });
	cout << "2.1.i) Liste des villes présentes :\n";
    for_each(   liste_villes.begin(), liste_villes.end(),
                [](const string & s){ cout << "- " << s << "\n";} );
    

    // question 2.2
    ofstream fichierTri("data_tri.txt");
    vector<Fiche> vdata_tri(100);
    partial_sort_copy(   vdata.begin(), vdata.end(), vdata_tri.begin(), vdata_tri.end(),
            [](const Fiche & f1, const Fiche & f2){   return f1.temps > f2.temps;} );
	for_each(	vdata_tri.begin(), vdata_tri.end(),
				[& fichierTri](const Fiche & f){ fichierTri << f.prenom << "\t" << f.ville << "\t" << f.age << "\t" << f.temps << "\n";} );
    fichierTri.close();


    // **************************************************
    // question 3
	vector<double> difference_temps;
    transform(	vdata.begin(), vdata.end(), back_inserter(difference_temps),
				[](const Fiche & f) { return f.temps; });
    sort(difference_temps.begin(), difference_temps.end());
    adjacent_difference(difference_temps.begin(), difference_temps.end(), difference_temps.begin());
    sort(difference_temps.begin(), difference_temps.end());
    cout << "3.1) Plus petit écart entre deux temps du 100m : " << difference_temps.front() << "\n";

    vector<Fiche> jeunes;
    vector<Fiche> moinsjeunes;
    partition_copy(	vdata.begin(), vdata.end(), back_inserter(jeunes), back_inserter(moinsjeunes),
					[](const Fiche & f){	return f.age <= 40;});
	cout << "3.2)	Age de l'un des jeunes : " << jeunes.back().age << "\n";
	cout << "	Age de l'un des moins jeunes : " << moinsjeunes.back().age << "\n";
    
    ofstream ordre("ordre.dat");
    vector<Fiche> ordres(vdata.size());
    partial_sort_copy(	vdata.begin(), vdata.end(), ordres.begin(), ordres.end(),
						[](const Fiche & f1, const Fiche & f2){
							if (f1.prenom==f2.prenom){
								if (f1.ville==f2.ville){
									if (f1.age==f2.age){
										return f1#include <iostream>
#include <fstream>

#include <vector>
#include <set>
#include <cmath>
#include <string>

#include <algorithm>
#include <numeric>
#include <iterator>
#include <map>

using namespace std;

struct Fiche{
    string prenom;
    string ville;
    int age;
    double temps;
};

// *******************
// version alternative question 1.4
vector<Fiche> initialisation(string nomFichier){

    ifstream fichierdata(nomFichier);
    vector<string> data;
    string ligne;

    while (getline(fichierdata,ligne)) {
        /* récupère les lignes dans un vecteur */
        data.push_back(ligne);
    }
    fichierdata.close();


    // Création des fiches
    vector<Fiche> vfiche;

    for (string s : data){
        /* pour chaque string du vecteur data */
        vector<string> subs;

        size_t pos = s.find("\t", 0);   // première position d'une tabulation
        string sub = s.substr(0,pos);     // tire la substring avant la première tabulation
        subs.push_back(sub);

        // check les autres tabulations
        while(pos != string::npos){
            size_t pos2 = s.find("\t",pos+1);     // trouve la prochaine tabulation

            sub = s.substr(pos+1,pos2-(pos+1));     // tire la substring entre les deux tabulations
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

    return vfiche;
}


// *******************
int main(){
	int N = 2500;

    // question 1.2
    /* ifstream fichierdata("smalldata.txt");
    vector<Fiche> vdata(N);
    for(int i=0; i<N ; i++){
        Fiche aux;
        fichier >> aux.prenom >> aux.ville >> aux.age >> aux.temps;

        vdata[i] = aux;
    } */


    // question 1.4
    string prenom;
    string ville;
    int age;
    double temps;
    ifstream fichierdata("smalldata.txt");
    vector<Fiche> vdata;
    while(fichierdata >> prenom >> ville >> age >> temps){
        Fiche aux;
        aux.prenom = prenom;
        aux.ville = ville;
        aux.age = age;
        aux.temps = temps;

        vdata.push_back(aux);
    }

    // question 1.4 autre version
    // Erreur de segmentation ! Pas sur les ordi de la fac o_O?
    /* vector<Fiche> vdata;
    vdata = initialisation("smalldata.txt"); */



    // **************************************************
    // question 1.3
    cout << "Sans <algorithm>\n";
    int countLyon = 0;
    int count30 = 0;
    for(const Fiche & f : vdata){
        if (f.ville == "Lyon"){
            countLyon++;
            if (f.age < 30){
                count30++;
            }
        }
    }
    cout    << "1.3.a) Nombre de personnes à Lyon (proportion) : " << countLyon#include <iostream>
#include <fstream>

#include <vector>
#include <set>
#include <cmath>
#include <string>

#include <algorithm>
#include <numeric>
#include <iterator>
#include <map>

using namespace std;

struct Fiche{
    string prenom;
    string ville;
    int age;
    double temps;
};

// *******************
// version alternative question 1.4
vector<Fiche> initialisation(string nomFichier){

    ifstream fichierdata(nomFichier);
    vector<string> data;
    string ligne;

    while (getline(fichierdata,ligne)) {
        /* récupère les lignes dans un vecteur */
        data.push_back(ligne);
    }
    fichierdata.close();


    // Création des fiches
    vector<Fiche> vfiche;

    for (string s : data){
        /* pour chaque string du vecteur data */
        vector<string> subs;

        size_t pos = s.find("\t", 0);   // première position d'une tabulation
        string sub = s.substr(0,pos);     // tire la substring avant la première tabulation
        subs.push_back(sub);

        // check les autres tabulations
        while(pos != string::npos){
            size_t pos2 = s.find("\t",pos+1);     // trouve la prochaine tabulation

            sub = s.substr(pos+1,pos2-(pos+1));     // tire la substring entre les deux tabulations
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

    return vfiche;
}


// *******************
int main(){
	int N = 2500;

    // question 1.2
    /* ifstream fichierdata("smalldata.txt");
    vector<Fiche> vdata(N);
    for(int i=0; i<N ; i++){
        Fiche aux;
        fichier >> aux.prenom >> aux.ville >> aux.age >> aux.temps;

        vdata[i] = aux;
    } */


    // question 1.4
    string prenom;
    string ville;
    int age;
    double temps;
    ifstream fichierdata("smalldata.txt");
    vector<Fiche> vdata;
    while(fichierdata >> prenom >> ville >> age >> temps){
        Fiche aux;
        aux.prenom = prenom;
        aux.ville = ville;
        aux.age = age;
        aux.temps = temps;

        vdata.push_back(aux);
    }

    // question 1.4 autre version
    // Erreur de segmentation ! Pas sur les ordi de la fac o_O?
    /* vector<Fiche> vdata;
    vdata = initialisation("smalldata.txt"); */



    // **************************************************
    // question 1.3
    cout << "Sans <algorithm>\n";
    int countLyon = 0;
    int count30 = 0;
    for(const Fiche & f : vdata){
        if (f.ville == "Lyon"){
            countLyon++;
            if (f.age < 30){
                count30++;
            }
        }
    }
    cout    << "1.3.a) Nombre de personnes à Lyon (proportion) : " << countLyon
            << " (" << 100*double(countLyon)/N << "%)\n";
    cout << "1.3.b) ---> de moins de 30ans : " << count30 << "\n";

    int countA=0;
    vector<string> prenoms;
    for(const Fiche & f : vdata){
        if ((f.ville == "Toulouse") && (f.prenom.front() == 'A')){
            countA++;
            prenoms.push_back(f.prenom);
        }
    }
    cout << "1.3.c) Un Toulousain dont le prénom commance par \'A\' : " << ((countA > 0) ? "Oui\n" : "Non\n");
    cout << "---> il y en a " << countA << " et le premier s'appelle " << prenoms.front() << "\n";

    int ind_min = 0;
    int ind_max = 0;
    for(int i=1; i<N ; i++){
        if (vdata[i].age < vdata[ind_min].age){
            ind_min=i;
        } else if (vdata[i].age > vdata[ind_max].age){
            ind_max=i;
        }
    }
    cout << "1.3.d) Âge minimal : " << vdata[ind_min].age << " (" << vdata[ind_min].prenom << ")\n";
    cout << "       Âge maximal : " << vdata[ind_max].age << " (" << vdata[ind_max].prenom << ")\n";

    double moyenne=0.;
    double ecart_type=0.;
    for(const Fiche & f : vdata){
        moyenne += f.age;
        ecart_type += f.age * f.age;
    }
    moyenne /= N;
    ecart_type = sqrt(ecart_type/N - moyenne*moyenne);
    cout << "1.3.e) Âge moyen : " << moyenne << ", écart-type : " << ecart_type << "\n";

    double tpsParis=0., tpsMarseille=0.;
    int countParis=0, countMarseille=0;
    for(const Fiche & f : vdata){
        if (f.ville == "Paris"){
            tpsParis += f.temps;
            countParis++;
        } else if (f.ville == "Marseille"){
            tpsMarseille += f.temps;
            countMarseille++;
        }
    }
    cout	<< "1.3.f) Les Parisiens en moyenne plus rapide que les Marseillais ? "
            << ((tpsParis/countParis > tpsMarseille/countMarseille) ? "Oui" : "Non") << "\n";
    cout << "---> Paris : " << tpsParis/countParis << "\n---> Marseille : " << tpsMarseille/countMarseille << "\n";

    // question 3.g)
    vector<Fiche> ficheT;
    int compt=0;
    ofstream fichierT("toulousain.txt");
    for (const Fiche & f : vdata){
        if (f.ville == "Toulouse"){
	        compt++;
	        
            Fiche aux;
            aux.prenom = f.prenom;
            aux.ville = f.ville;
            aux.age = f.age;
            aux.temps = f.temps;

            ficheT.push_back(aux);
            fichierT << f.prenom << "\t" << f.ville << "\t" << 2018-f.age << "\t" << f.temps << "\n";
        }
    }
    fichierT.close();
    
    int ageT=0;
    double tempsT=0.;
    double agetempsT=0.;
    for(const Fiche & f : ficheT){
        ageT += f.age;
        tempsT += f.temps;
        agetempsT += f.age*f.temps;
    }
    double covAgeTempsT = agetempsT/compt - (double(ageT)/compt)*(tempsT/compt);    // cov(X,Y) = E[XY] - E[X]E[Y]
    cout << "1.3.h) Covariance empirique entre âge et temps au 100 mètres pour les Toulousains : " << covAgeTempsT << "\n";

    set<string> villes;
    for(const Fiche & f : vdata){
		villes.insert(f.ville);
	}
	cout << "1.3.i) Liste des villes présentes (avec set) :\n";
	for(string s : villes){
		cout << "- " << s << "\n";
	}


    // **************************************************
    // question 2.1
    cout << endl << "Avec <algorithm>\n";
    int nb_Lyon = count_if( vdata.begin(), vdata.end(),
                            [](const Fiche & f){    return (f.ville == "Lyon");} );
    int nb_Lyon30 = count_if(   vdata.begin(), vdata.end(),
                                [](const Fiche & f){    return ((f.ville == "Lyon") && (f.age < 30));} );
    cout << "2.1.a) Nombre de personnes à Lyon (proportion) : " << nb_Lyon << " (" << 100*double(nb_Lyon)/N << "%)\n";
    cout << "2.1.b) ---> de moins de 30ans : " << nb_Lyon30 << "\n";

    bool is_TA = any_of(    vdata.begin(), vdata.end(),
                            [](const Fiche & f){    return ((f.ville == "Toulouse") && (f.prenom.front()=='A'));} );
    cout << "2.1.c) Un Toulousain dont le prénom commance par \'A\' : " << (is_TA ? "Oui\n" : "Non\n");

    auto minmax = minmax_element(   vdata.begin(), vdata.end(),
                                    [](const Fiche & f1, const Fiche & f2){ return f1.age < f2.age;} );
    cout << "2.1.d)	Âge minimal : " << minmax.first->age << " (" << minmax.first->prenom << ")\n";
    cout << "       Âge maximal : " << minmax.second->age << " (" << minmax.second->prenom << ")\n";
    /* Autre méthode pour les pointeurs !
    cout << "2.1.d)	Âge minimal : " << (*minmax.first).age << " (" << (*minmax.first).prenom << ")" << endl;
    cout << "       Âge maximal : " << (*minmax.second).age << " (" << (*minmax.second).prenom << ")" << endl; */
    
    double moy_age = accumulate(	vdata.begin(), vdata.end(), 0.,
									[N](double sum, const Fiche & f){	return sum + double(f.age)/N;} );
    double moy_age_carre = accumulate(	vdata.begin(), vdata.end(), 0.,
										[N](double sum, const Fiche & f){	return sum + double(f.age*f.age)/N;} );
    double ecart_age = sqrt(moy_age_carre - moy_age*moy_age);
    cout << "2.1.e) Âge moyen : " << moy_age << ", écart-type : " << ecart_age << endl;

    double temps_Paris = accumulate(	vdata.begin(), vdata.end(), 0.,
									    [](double sum, const Fiche & f){	return (f.ville == "Paris") ? sum + f.temps : sum;} );
    double temps_Marseille = accumulate(	vdata.begin(), vdata.end(), 0.,
										    [](double sum, const Fiche & f){	return (f.ville == "Marseille") ? sum + f.temps : sum;} );
    int nb_Paris = count_if(	vdata.begin(), vdata.end(),
								[](const Fiche & f){    return (f.ville == "Paris");} );
    int nb_Marseille = count_if(	vdata.begin(), vdata.end(),
									[](const Fiche & f){    return (f.ville == "Marseille");} );
    cout    << "2.1.f) Les Parisiens en moyenne plus rapide que les Marseillais ? "
            << ((temps_Paris/nb_Paris > temps_Marseille/nb_Marseille) ? "Oui\n" : "Non\n");
    cout << "---> Paris : " << temps_Paris/nb_Paris << "\n---> Marseille : " << temps_Marseille/nb_Marseille << "\n";
    
    ofstream fichierT2("toulousain_algo.txt");
    for_each(   vdata.begin(), vdata.end(),
                [& fichierT2](const Fiche & f){    if (f.ville == "Toulouse") fichierT2 << f.prenom << "\t" << f.ville << "\t" << 2018-f.age << "\t" << f.temps << "\n";} );
    fichierT2.close();

    int nb_Toulouse = count_if(	vdata.begin(), vdata.end(),
								[](const Fiche & f){    return (f.ville == "Toulouse");} );
    double moy_temps_Toulouse = accumulate(	vdata.begin(), vdata.end(), 0.,
										    [nb_Toulouse](double sum, const Fiche & f){	return (f.ville == "Toulouse") ? sum + f.temps/nb_Toulouse: sum;} );
    double moy_age_Toulouse = accumulate(	vdata.begin(), vdata.end(), 0.,
										    [nb_Toulouse](double sum, const Fiche & f){	return (f.ville == "Toulouse") ? sum + double(f.age)/nb_Toulouse : sum;} );
    double moy_agetemps_Toulouse = accumulate(	vdata.begin(), vdata.end(), 0.,
										        [nb_Toulouse](double sum, const Fiche & f){	return (f.ville == "Toulouse") ? sum + f.temps*f.age/nb_Toulouse : sum;} );
    double cov_agetemps_Toulouse = moy_agetemps_Toulouse - moy_temps_Toulouse*moy_age_Toulouse;    // cov(X,Y) = E[XY] - E[X]E[Y]
    cout << "2.1.h) Covariance empirique entre âge et temps au 100 mètres pour les Toulousains : " << cov_agetemps_Toulouse << "\n";

    set<string> liste_villes;
    transform(	vdata.begin(), vdata.end(), inserter(liste_villes,liste_villes.end()),
				[](const Fiche & f) { return f.ville; });
	cout << "2.1.i) Liste des villes présentes :\n";
    for_each(   liste_villes.begin(), liste_villes.end(),
                [](const string & s){ cout << "- " << s << "\n";} );
    

    // question 2.2
    ofstream fichierTri("data_tri.txt");
    vector<Fiche> vdata_tri(100);
    partial_sort_copy(   vdata.begin(), vdata.end(), vdata_tri.begin(), vdata_tri.end(),
            [](const Fiche & f1, const Fiche & f2){   return f1.temps > f2.temps;} );
	for_each(	vdata_tri.begin(), vdata_tri.end(),
				[& fichierTri](const Fiche & f){ fichierTri << f.prenom << "\t" << f.ville << "\t" << f.age << "\t" << f.temps << "\n";} );
    fichierTri.close();


    // **************************************************
    // question 3
	vector<double> difference_temps;
    transform(	vdata.begin(), vdata.end(), back_inserter(difference_temps),
				[](const Fiche & f) { return f.temps; });
    sort(difference_temps.begin(), difference_temps.end());
    adjacent_difference(difference_temps.begin(), difference_temps.end(), difference_temps.begin());
    sort(difference_temps.begin(), difference_temps.end());
    cout << "3.1) Plus petit écart entre deux temps du 100m : " << difference_temps.front() << "\n";

    vector<Fiche> jeunes;
    vector<Fiche> moinsjeunes;
    partition_copy(	vdata.begin(), vdata.end(), back_inserter(jeunes), back_inserter(moinsjeunes),
					[](const Fiche & f){	return f.age <= 40;});
	cout << "3.2)	Age de l'un des jeunes : " << jeunes.back().age << "\n";
	cout << "	Age de l'un des moins jeunes : " << moinsjeunes.back().age << "\n";
    
    ofstream ordre("ordre.dat");
    vector<Fiche> ordres(vdata.size());
    partial_sort_copy(	vdata.begin(), vdata.end(), ordres.begin(), ordres.end(),
						[](const Fiche & f1, const Fiche & f2){
							if (f1.prenom==f2.prenom){
								if (f1.ville==f2.ville){
									if (f1.age==f2.age){
										return f1.temps<f2.temps;
									} else {	return f1.age>f2.age; }
								} else {	return f1.ville<f2.ville; }
							} else {	return f1.prenom<f2.prenom; }
						});
	for_each(	ordres.begin(), ordres.end(),
				[& ordre](const Fiche & f){ ordre << f.prenom << "\t" << f.ville << "\t" << f.age << "\t" << f.temps << "\n";} );
    ordre.close();
    
    map<int,int> hist_age;
    for_each(	vdata.begin(), vdata.end(),
				[& hist_age](const Fiche & f){	hist_age[f.age]++; });
	cout << "Histogramme numérique des âges : \n";
	for (const auto& [key, val] : hist_age)
			cout << "[" << key << "] = " << val << "\n";
	

    return 0;
}

            << " (" << 100*double(countLyon)/N << "%)\n";
    cout << "1.3.b) ---> de moins de 30ans : " << count30 << "\n";

    int countA=0;
    vector<string> prenoms;
    for(const Fiche & f : vdata){
        if ((f.ville == "Toulouse") && (f.prenom.front() == 'A')){
            countA++;
            prenoms.push_back(f.prenom);
        }
    }
    cout << "1.3.c) Un Toulousain dont le prénom commance par \'A\' : " << ((countA > 0) ? "Oui\n" : "Non\n");
    cout << "---> il y en a " << countA << " et le premier s'appelle " << prenoms.front() << "\n";

    int ind_min = 0;
    int ind_max = 0;
    for(int i=1; i<N ; i++){
        if (vdata[i].age < vdata[ind_min].age){
            ind_min=i;
        } else if (vdata[i].age > vdata[ind_max].age){
            ind_max=i;
        }
    }
    cout << "1.3.d) Âge minimal : " << vdata[ind_min].age << " (" << vdata[ind_min].prenom << ")\n";
    cout << "       Âge maximal : " << vdata[ind_max].age << " (" << vdata[ind_max].prenom << ")\n";

    double moyenne=0.;
    double ecart_type=0.;
    for(const Fiche & f : vdata){
        moyenne += f.age;
        ecart_type += f.age * f.age;
    }
    moyenne /= N;
    ecart_type = sqrt(ecart_type/N - moyenne*moyenne);
    cout << "1.3.e) Âge moyen : " << moyenne << ", écart-type : " << ecart_type << "\n";

    double tpsParis=0., tpsMarseille=0.;
    int countParis=0, countMarseille=0;
    for(const Fiche & f : vdata){
        if (f.ville == "Paris"){
            tpsParis += f.temps;
            countParis++;
        } else if (f.ville == "Marseille"){
            tpsMarseille += f.temps;
            countMarseille++;
        }
    }
    cout	<< "1.3.f) Les Parisiens en moyenne plus rapide que les Marseillais ? "
            << ((tpsParis/countParis > tpsMarseille/countMarseille) ? "Oui" : "Non") << "\n";
    cout << "---> Paris : " << tpsParis/countParis << "\n---> Marseille : " << tpsMarseille/countMarseille << "\n";

    // question 3.g)
    vector<Fiche> ficheT;
    int compt=0;
    ofstream fichierT("toulousain.txt");
    for (const Fiche & f : vdata){
        if (f.ville == "Toulouse"){
	        compt++;
	        
            Fiche aux;
            aux.prenom = f.prenom;
            aux.ville = f.ville;
            aux.age = f.age;
            aux.temps = f.temps;

            ficheT.push_back(aux);
            fichierT << f.prenom << "\t" << f.ville << "\t" << 2018-f.age << "\t" << f.temps << "\n";
        }
    }
    fichierT.close();
    
    int ageT=0;
    double tempsT=0.;
    double agetempsT=0.;
    for(const Fiche & f : ficheT){
        ageT += f.age;
        tempsT += f.temps;
        agetempsT += f.age*f.temps;
    }
    double covAgeTempsT = agetempsT/compt - (double(ageT)/compt)*(tempsT/compt);    // cov(X,Y) = E[XY] - E[X]E[Y]
    cout << "1.3.h) Covariance empirique entre âge et temps au 100 mètres pour les Toulousains : " << covAgeTempsT << "\n";

    set<string> villes;
    for(const Fiche & f : vdata){
		villes.insert(f.ville);
	}
	cout << "1.3.i) Liste des villes présentes (avec set) :\n";
	for(string s : villes){
		cout << "- " << s << "\n";
	}


    // **************************************************
    // question 2.1
    cout << endl << "Avec <algorithm>\n";
    int nb_Lyon = count_if( vdata.begin(), vdata.end(),
                            [](const Fiche & f){    return (f.ville == "Lyon");} );
    int nb_Lyon30 = count_if(   vdata.begin(), vdata.end(),
                                [](const Fiche & f){    return ((f.ville == "Lyon") && (f.age < 30));} );
    cout << "2.1.a) Nombre de personnes à Lyon (proportion) : " << nb_Lyon << " (" << 100*double(nb_Lyon)/N << "%)\n";
    cout << "2.1.b) ---> de moins de 30ans : " << nb_Lyon30 << "\n";

    bool is_TA = any_of(    vdata.begin(), vdata.end(),
                            [](const Fiche & f){    return ((f.ville == "Toulouse") && (f.prenom.front()=='A'));} );
    cout << "2.1.c) Un Toulousain dont le prénom commance par \'A\' : " << (is_TA ? "Oui\n" : "Non\n");

    auto minmax = minmax_element(   vdata.begin(), vdata.end(),
                                    [](const Fiche & f1, const Fiche & f2){ return f1.age < f2.age;} );
    cout << "2.1.d)	Âge minimal : " << minmax.first->age << " (" << minmax.first->prenom << ")\n";
    cout << "       Âge maximal : " << minmax.second->age << " (" << minmax.second->prenom << ")\n";
    /* Autre méthode pour les pointeurs !
    cout << "2.1.d)	Âge minimal : " << (*minmax.first).age << " (" << (*minmax.first).prenom << ")" << endl;
    cout << "       Âge maximal : " << (*minmax.second).age << " (" << (*minmax.second).prenom << ")" << endl; */
    
    double moy_age = accumulate(	vdata.begin(), vdata.end(), 0.,
									[N](double sum, const Fiche & f){	return sum + double(f.age)/N;} );
    double moy_age_carre = accumulate(	vdata.begin(), vdata.end(), 0.,
										[N](double sum, const Fiche & f){	return sum + double(f.age*f.age)/N;} );
    double ecart_age = sqrt(moy_age_carre - moy_age*moy_age);
    cout << "2.1.e) Âge moyen : " << moy_age << ", écart-type : " << ecart_age << endl;

    double temps_Paris = accumulate(	vdata.begin(), vdata.end(), 0.,
									    [](double sum, const Fiche & f){	return (f.ville == "Paris") ? sum + f.temps : sum;} );
    double temps_Marseille = accumulate(	vdata.begin(), vdata.end(), 0.,
										    [](double sum, const Fiche & f){	return (f.ville == "Marseille") ? sum + f.temps : sum;} );
    int nb_Paris = count_if(	vdata.begin(), vdata.end(),
								[](const Fiche & f){    return (f.ville == "Paris");} );
    int nb_Marseille = count_if(	vdata.begin(), vdata.end(),
									[](const Fiche & f){    return (f.ville == "Marseille");} );
    cout    << "2.1.f) Les Parisiens en moyenne plus rapide que les Marseillais ? "
            << ((temps_Paris/nb_Paris > temps_Marseille/nb_Marseille) ? "Oui\n" : "Non\n");
    cout << "---> Paris : " << temps_Paris/nb_Paris << "\n---> Marseille : " << temps_Marseille/nb_Marseille << "\n";
    
    ofstream fichierT2("toulousain_algo.txt");
    for_each(   vdata.begin(), vdata.end(),
                [& fichierT2](const Fiche & f){    if (f.ville == "Toulouse") fichierT2 << f.prenom << "\t" << f.ville << "\t" << 2018-f.age << "\t" << f.temps << "\n";} );
    fichierT2.close();

    int nb_Toulouse = count_if(	vdata.begin(), vdata.end(),
								[](const Fiche & f){    return (f.ville == "Toulouse");} );
    double moy_temps_Toulouse = accumulate(	vdata.begin(), vdata.end(), 0.,
										    [nb_Toulouse](double sum, const Fiche & f){	return (f.ville == "Toulouse") ? sum + f.temps/nb_Toulouse: sum;} );
    double moy_age_Toulouse = accumulate(	vdata.begin(), vdata.end(), 0.,
										    [nb_Toulouse](double sum, const Fiche & f){	return (f.ville == "Toulouse") ? sum + double(f.age)/nb_Toulouse : sum;} );
    double moy_agetemps_Toulouse = accumulate(	vdata.begin(), vdata.end(), 0.,
										        [nb_Toulouse](double sum, const Fiche & f){	return (f.ville == "Toulouse") ? sum + f.temps*f.age/nb_Toulouse : sum;} );
    double cov_agetemps_Toulouse = moy_agetemps_Toulouse - moy_temps_Toulouse*moy_age_Toulouse;    // cov(X,Y) = E[XY] - E[X]E[Y]
    cout << "2.1.h) Covariance empirique entre âge et temps au 100 mètres pour les Toulousains : " << cov_agetemps_Toulouse << "\n";

    set<string> liste_villes;
    transform(	vdata.begin(), vdata.end(), inserter(liste_villes,liste_villes.end()),
				[](const Fiche & f) { return f.ville; });
	cout << "2.1.i) Liste des villes présentes :\n";
    for_each(   liste_villes.begin(), liste_villes.end(),
                [](const string & s){ cout << "- " << s << "\n";} );
    

    // question 2.2
    ofstream fichierTri("data_tri.txt");
    vector<Fiche> vdata_tri(100);
    partial_sort_copy(   vdata.begin(), vdata.end(), vdata_tri.begin(), vdata_tri.end(),
            [](const Fiche & f1, const Fiche & f2){   return f1.temps > f2.temps;} );
	for_each(	vdata_tri.begin(), vdata_tri.end(),
				[& fichierTri](const Fiche & f){ fichierTri << f.prenom << "\t" << f.ville << "\t" << f.age << "\t" << f.temps << "\n";} );
    fichierTri.close();


    // **************************************************
    // question 3
	vector<double> difference_temps;
    transform(	vdata.begin(), vdata.end(), back_inserter(difference_temps),
				[](const Fiche & f) { return f.temps; });
    sort(difference_temps.begin(), difference_temps.end());
    adjacent_difference(difference_temps.begin(), difference_temps.end(), difference_temps.begin());
    sort(difference_temps.begin(), difference_temps.end());
    cout << "3.1) Plus petit écart entre deux temps du 100m : " << difference_temps.front() << "\n";

    vector<Fiche> jeunes;
    vector<Fiche> moinsjeunes;
    partition_copy(	vdata.begin(), vdata.end(), back_inserter(jeunes), back_inserter(moinsjeunes),
					[](const Fiche & f){	return f.age <= 40;});
	cout << "3.2)	Age de l'un des jeunes : " << jeunes.back().age << "\n";
	cout << "	Age de l'un des moins jeunes : " << moinsjeunes.back().age << "\n";
    
    ofstream ordre("ordre.dat");
    vector<Fiche> ordres(vdata.size());
    partial_sort_copy(	vdata.begin(), vdata.end(), ordres.begin(), ordres.end(),
						[](const Fiche & f1, const Fiche & f2){
							if (f1.prenom==f2.prenom){
								if (f1.ville==f2.ville){
									if (f1.age==f2.age){
										return f1.temps<f2.temps;
									} else {	return f1.age>f2.age; }
								} else {	return f1.ville<f2.ville; }
							} else {	return f1.prenom<f2.prenom; }
						});
	for_each(	ordres.begin(), ordres.end(),
				[& ordre](const Fiche & f){ ordre << f.prenom << "\t" << f.ville << "\t" << f.age << "\t" << f.temps << "\n";} );
    ordre.close();
    
    map<int,int> hist_age;
    for_each(	vdata.begin(), vdata.end(),
				[& hist_age](const Fiche & f){	hist_age[f.age]++; });
	cout << "Histogramme numérique des âges : \n";
	for (const auto& [key, val] : hist_age)
			cout << "[" << key << "] = " << val << "\n";
	

    return 0;
}
.temps<f2.temps;
									} else {	return f1.age>f2.age; }
								} else {	return f1.ville<f2.ville; }
							} else {	return f1.prenom<f2.prenom; }
						});
	for_each(	ordres.begin(), ordres.end(),
				[& ordre](const Fiche & f){ ordre << f.prenom << "\t" << f.ville << "\t" << f.age << "\t" << f.temps << "\n";} );
    ordre.close();
    
    map<int,int> hist_age;
    for_each(	vdata.begin(), vdata.end(),
				[& hist_age](const Fiche & f){	hist_age[f.age]++; });
	cout << "Histogramme numérique des âges : \n";
	for (const auto& [key, val] : hist_age)
			cout << "[" << key << "] = " << val << "\n";
	

    return 0;
}
