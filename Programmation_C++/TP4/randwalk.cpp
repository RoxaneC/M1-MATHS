#include "randwalk.hpp"

#include <random>
#include <ctime>
#include <iostream>
#include <fstream>

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


int main(){
    // question 4.2
    RandomWalk RW(0, 0.5);
    mt19937 Gen(time(NULL));

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

    return 0;
}