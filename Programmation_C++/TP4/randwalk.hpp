#ifndef MY_RAND_WALK
#define MY_RAND_WALK

#include <random>

class RandomWalk;
class RandomWalk_with_Min;

class RandomWalk{
    protected:
        unsigned n; // temps courant n
        int s; // valeur de S_n
        int s_init; // valeur de S_0
        std::bernoulli_distribution U; // paramètre p

    public:
        RandomWalk(int s0, double p);

        int val() const {   return s; }; // accesseur s
        unsigned time() const { return n; }; // accesseur n

        virtual void reset(); // redémarrage à l'état initial

        template <typename Alea>
        void update(Alea &G); // maj de s : passage de S_n à S_n+1 avec un générateur G de type arbitraire
};

class RandomWalk_with_Min: public RandomWalk{
    protected:
        int m; // valeur de M_n
    
    public:
        RandomWalk_with_Min(int s0, double p): RandomWalk(s0, p), m(s0){};

        int minimum() const {   return m; }; // accesseur à m

        void reset(); // redémarrage à l'état initial

        template <typename Alea>
        void update(Alea &G);
};

#endif