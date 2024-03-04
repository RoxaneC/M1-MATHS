#include "sandpile.hpp"

#include <vector>
#include <list>
#include <utility>
#include <fstream>

using upair=std::pair<unsigned, unsigned>; //raccourci pour les paires d'entiers
using namespace std;

int main() {
    // question 5
    Sandpile s(8,8,5);
    cout << "La hauteur de sable en (1,1) est " << s(1,1) << endl;
    cout << "La configuration complète est :" << endl << s;

    // question 8
    cout << "Nb de voisins de (0,0) : " << s.voisins(upair(0,0)).size() << "\n"; // 2 OK
    cout << "Nb de voisins de (1,2) : " << s.voisins(upair(1,2)).size() << "\n\n"; // 4 OK

    // question 13
    s.stabil();
    // cout << s.volume_total();
    ofstream file("stab_8x8_5.txt");
    file << s.nb_total_ebouls() << "\n";    // 564 OK
    file << s;
    file.close();

    // question 14
    Sandpile t(100, 100, 4);
    t.stabil();
    cout << t << "\n";

    // question 16
    mt19937 G(time(NULL));
    Sandpile t2(100, 100, 4);
    t2.add_random_grain(G, 3);
    cout << t2 << "\n";

    // test question 17
    Sandpile test = s+s;
    cout << test;

    return 0;
}