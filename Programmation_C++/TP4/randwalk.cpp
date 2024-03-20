#include "randwalk.hpp"

#include <random>
#include <ctime>
#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <deque>
// #include <list>

using namespace std;

// question 4.1
RandomWalk::RandomWalk(int s0, double p): s_init(s0), n(0), s(s0), U(p){};

void RandomWalk::reset(){
    n = 0; s = 0;
};

template <typename Alea>
void RandomWalk::update(Alea &G){
    s += U(G) ? 1 : -1;
    n++;
};

// question 4.3
void RandomWalk_with_Min::reset(){
    RandomWalk::reset();
    m = s_init;
};

template <typename Alea>
void RandomWalk_with_Min::update(Alea &G){
    RandomWalk::update(G);
    m = (val() < m) ? val() : m;
};

// question 4.6
void measure_complexity_on_vector(long int N, mt19937 &G){
    vector<double> c1(N);
    vector<double> c2(N);
    exponential_distribution<double> E(1);

    auto t1 = chrono::system_clock::now();
    for(int i=0 ; i<N ; i++)    c1[i] = E(G);
    auto t2 = chrono::system_clock::now();
    chrono::duration<double> tps = t2-t1;
    cout << "Le remplissage de c1 dure : " << tps.count() << " seconde.\n";

    t1 = chrono::system_clock::now();
    int inf_10_1 = count_if(    c1.begin(), c1.end(),
                                [](const double &d){   return d>10;} );
    t2 = chrono::system_clock::now();
    tps = t2-t1;
    cout << "Le comptage des éléments >10 de c1 dure : " << tps.count() << " seconde.\n";

    t1 = chrono::system_clock::now();
    transform( c1.begin(), c1.begin()+100, c1.begin(),
                []( double &d){    return d*d;} );
    t2 = chrono::system_clock::now();
    tps = t2-t1;
    cout << "L'élévation au carré des 100 premier elem de c1 dure : " << tps.count() << " seconde.\n";

    t1 = chrono::system_clock::now();
    copy(c1.begin(), c1.end(), c2.begin());
    t2 = chrono::system_clock::now();
    tps = t2-t1;
    cout << "La copie de c1 dans c2 dure : " << tps.count() << " seconde.\n";

    t1 = chrono::system_clock::now();
    sort(c1.begin(), c1.begin()+N/2);
    t2 = chrono::system_clock::now();
    tps = t2-t1;
    cout << "Le tri de la moitié de c1 dure : " << tps.count() << " seconde.\n";

    t1 = chrono::system_clock::now();
    swap(c1, c2);
    t2 = chrono::system_clock::now();
    tps = t2-t1;
    cout << "Le swap entre c1 et c2 dure : " << tps.count() << " seconde.\n";

    t1 = chrono::system_clock::now();
    ofstream file("chocolatine.cpp");
    for(int i=0 ; i<c2.size() ; i++)    file << c2[i] << "\n";
    file.close();
    t2 = chrono::system_clock::now();
    tps = t2-t1;
    cout << "L'écriture de c2 dans un fichier dure : " << tps.count() << " seconde.\n";
}

// question 4.8
void measure_complexity_on_deque(long int N, mt19937 &G){
    deque<double> c1(N);
    deque<double> c2(N);
    exponential_distribution<double> E(1);

    auto t1 = chrono::system_clock::now();
    for(int i=0 ; i<N ; i++)    c1[i] = E(G);
    auto t2 = chrono::system_clock::now();
    chrono::duration<double> tps = t2-t1;
    cout << "Le remplissage de c1 dure : " << tps.count() << " seconde.\n";

    t1 = chrono::system_clock::now();
    int inf_10_1 = count_if(    c1.begin(), c1.end(),
                                [](const double &d){   return d>10;} );
    t2 = chrono::system_clock::now();
    tps = t2-t1;
    cout << "Le comptage des éléments >10 de c1 dure : " << tps.count() << " seconde.\n";

    t1 = chrono::system_clock::now();
    transform( c1.begin(), c1.begin()+100, c1.begin(),
                []( double &d){    return d*d;} );
    t2 = chrono::system_clock::now();
    tps = t2-t1;
    cout << "L'élévation au carré des 100 premier elem de c1 dure : " << tps.count() << " seconde.\n";

    t1 = chrono::system_clock::now();
    copy(c1.begin(), c1.end(), c2.begin());
    t2 = chrono::system_clock::now();
    tps = t2-t1;
    cout << "La copie de c1 dans c2 dure : " << tps.count() << " seconde.\n";

    t1 = chrono::system_clock::now();
    sort(c1.begin(), c1.begin()+N/2);
    t2 = chrono::system_clock::now();
    tps = t2-t1;
    cout << "Le tri de la moitié de c1 dure : " << tps.count() << " seconde.\n";

    t1 = chrono::system_clock::now();
    swap(c1, c2);
    t2 = chrono::system_clock::now();
    tps = t2-t1;
    cout << "Le swap entre c1 et c2 dure : " << tps.count() << " seconde.\n";

    t1 = chrono::system_clock::now();
    ofstream file("chocolatine.cpp");
    for(int i=0 ; i<c2.size() ; i++)    file << c2[i] << "\n";
    file.close();
    t2 = chrono::system_clock::now();
    tps = t2-t1;
    cout << "L'écriture de c2 dans un fichier dure : " << tps.count() << " seconde.\n";
}

// question 4.9
/* void measure_complexity_on_list(long int N, mt19937 &G){
    list<double> c1(N);
    list<double> c2(N);
    exponential_distribution<double> E(1);

    auto t1 = chrono::system_clock::now();
    for(int i=0 ; i<N ; i++)    c1[i] = E(G);
    auto t2 = chrono::system_clock::now();
    chrono::duration<double> tps = t2-t1;
    cout << "Le remplissage de c1 dure : " << tps.count() << " seconde.\n";

    t1 = chrono::system_clock::now();
    int inf_10_1 = count_if(    c1.begin(), c1.end(),
                                [](const double &d){   return d>10;} );
    t2 = chrono::system_clock::now();
    tps = t2-t1;
    cout << "Le comptage des éléments >10 de c1 dure : " << tps.count() << " seconde.\n";

    t1 = chrono::system_clock::now();
    transform( c1.begin(), c1.begin()+100, c1.begin(),
                []( double &d){    return d*d;} );
    t2 = chrono::system_clock::now();
    tps = t2-t1;
    cout << "L'élévation au carré des 100 premier elem de c1 dure : " << tps.count() << " seconde.\n";

    t1 = chrono::system_clock::now();
    copy(c1.begin(), c1.end(), c2.begin());
    t2 = chrono::system_clock::now();
    tps = t2-t1;
    cout << "La copie de c1 dans c2 dure : " << tps.count() << " seconde.\n";

    t1 = chrono::system_clock::now();
    swap(c1, c2);
    t2 = chrono::system_clock::now();
    tps = t2-t1;
    cout << "Le swap entre c1 et c2 dure : " << tps.count() << " seconde.\n";

    t1 = chrono::system_clock::now();
    ofstream file("chocolatine.cpp");
    for(int i=0 ; i<c2.size() ; i++)    file << c2[i] << "\n";
    file.close();
    t2 = chrono::system_clock::now();
    tps = t2-t1;
    cout << "L'écriture de c2 dans un fichier dure : " << tps.count() << " seconde.\n";
} */


int main(){
    // question 4.2
    RandomWalk RW(0, 0.5);
    mt19937 Gen(time(nullptr));

    cout << "S_" << RW.time() << " = " << RW.val() << "\n";

    for(int i=0 ; i<10 ; i++){
        RW.update(Gen);
        cout << "S_" << RW.time() << " = " << RW.val() << "\n";
    }

    // question 4.4
    RandomWalk_with_Min RWmin(0, 0.5);
    int T = 10000;

    ofstream file_rw("RW.dat");
    ofstream file_rw_min("RWmin.dat");
    for(int i=0 ; i<T ; i++){
        RWmin.update(Gen);
        file_rw << RWmin.time() << " " << RWmin.val() << "\n";
        file_rw_min << RWmin.time() << " " << RWmin.minimum() << "\n";
    }
    file_rw.close();
    file_rw_min.close();

    // question 4.7
    cout << "\n\nQuestion 4.7 : Timer Avec std::vector\n";
    int M = 10000000;
    for(int i : {1,2,4,8}){
        cout << "\tPour N = " << i*M << " : \n";
        measure_complexity_on_vector(i*M, Gen);
        cout << "\n";
    }

    // question 4.8
    cout << "\n\nQuestion 4.8 : Timer Avec std::deque\n";
    for(int i : {1,2,4,8}){
        cout << "\tPour N = " << i*M << " : \n";
        measure_complexity_on_deque(i*M, Gen);
        cout << "\n";
    }

    // question 4.9
    /* cout << "\n\nQuestion 4.8 : Timer Avec std::list\n";
    for(int i : {1,2,4,8}){
        cout << "\tPour N = " << i*M << " : \n";
        measure_complexity_on_list(i*M, Gen);
        cout << "\n";
    } */

    return 0;
}