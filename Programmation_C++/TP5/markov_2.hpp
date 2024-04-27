#ifndef MY_MARKOV
#define MY_MARKOV

#include <random>
#include <iostream>

// question 5.16
class Markov2states{
    protected:
        int x;
        std::bernoulli_distribution Ua;
        std::bernoulli_distribution Ub;

    public:
        Markov2states(int x0=1, double a0=0.5, double b0=0.5):
            x(x0),
            Ua(a0),
            Ub(b0)
            {};
        template <class RNG>
        int operator()(RNG &G);

};

template <class RNG>
int Markov2states::operator()(RNG &G){
    if(x==1)    x += Ua(G);
    else if(x==2)    x -= Ub(G);
    return x;
};

// question 5.17
class Stat2states{
    protected:
        double visit1;
        double visit2;
    public: 
        Stat2states(double _visit1=0., double _visit2=0.): visit1(_visit1), visit2(_visit2) {};
        void operator+=(const int x);
        void operator/=(const double n){     visit1 /= n; visit2 /= n; };
        friend std::ostream & operator<<(std::ostream &o, const Stat2states &S);
};

void Stat2states::operator+=(const int x){
    if(x==1)    visit1+=1.;
    if(x==2)    visit2+=1.;
};

std::ostream & operator<<(std::ostream &o, const Stat2states &S){
    o << "Proportion de visite en 1 : " << S.visit1 << "\n";
    o << "Proportion de visite en 2 : " << S.visit2 << "\n";
    return o;
};


#endif