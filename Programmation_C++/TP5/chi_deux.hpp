#ifndef MY_PI
#define MY_PI

#include <random>

// question 5.14
template <class Real, int k>
class Chi2_distribution{
    private:
        std::normal_distribution<Real> N;

    public:
        Chi2_distribution(): N();
        template <class RNG>
        Real operator()(RNG &G);

};

#endif