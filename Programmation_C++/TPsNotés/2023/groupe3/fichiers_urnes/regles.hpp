//NOM:
//PRENOM:
//# étudiant:

#include <array>

/* Règles de mise à jour de Polya */
// question 13
template <class Entier, int n>
void updatePolyaN(int j, std::array<Entier,n> & arr){
    arr[j]++;
}

/* Règles de mise à jour de Friedman */

class Friedman2 {
    private:
        int q;
        int r;
    public:
        Friedman2(int q0, int r0): q(q0), r(r0) {};
        // question 15
        void operator()(int j, std::array<int, 2> &arr) const;
};
