//NOM:
//PRENOM:
//# étudiant:

// à compléter
#include "urne.hpp"
#include "regles.hpp"
#include <vector>
#include <algorithm>

using namespace std;

// question 15
void Friedman2::operator()(int j, array<int, 2> &arr) const {
    arr[j] += q;
    arr[1-j] += r;
}

int main() {
    // question 6
    Urne<int> U;
    cout << U << "\n";

    // question 10
    mt19937 Gen(time(nullptr));
    auto updatePolya2 = [](int j, std::array<int, 2> & arr){    arr[j]++; };

    // question 11
    int size_prop = 10000;
    vector<double> prop(size_prop);
    for(int i=0 ; i<size_prop ; i++){
        U.reset();
        U.maj_p_fois(updatePolya2, Gen, 1000);
        prop[i] = U.fraction(0);
    }

    // question 12
    sort(prop.begin(), prop.end());
    for(int j=0 ; j<10 ; j++){
        cout << prop[double(size_prop)/10*j] << "\t";
        cout << "Attendu : " << double(j)/10 << "\n";
    }

    // question 14
    Urne<long, 7> urne7;
    cout << "\nAvant : " << urne7 << "\n";
    urne7.maj(updatePolyaN<long,7>, Gen);
    cout << "Après : " << urne7 << "\n\n";

    // question 16
    Friedman2 updateF(7, 2);
    // question 17
    vector<double> propF(size_prop);
    for(int i=0 ; i<size_prop ; i++){
        U.reset();
        U.maj_p_fois(updateF, Gen, 1000);
        propF[i] = U.fraction(0);
    }
    sort(propF.begin(), propF.end());
    for(int j=0 ; j<10 ; j++){
        cout << propF[double(size_prop)/10*j] << "\n";
    }
    cout << "Attendu : 1/2 ?\n";

    return 0;
}

