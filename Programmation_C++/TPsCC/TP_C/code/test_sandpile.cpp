#include "sandpile.hpp"
#include <fstream>

int main() {

    Sandpile s(8, 8, 5);
    std::cout << "La hauteur de sable en (1,1) est " << s(1, 1) << std::endl;
    std::cout << "La configuration complète est :" << std::endl << s;

    std::cout << "la case (0,0) a " << s.voisins(upair(0, 0)).size()
              << "voisins." << std::endl;
    std::cout << "la case (1,2) a " << s.voisins(upair(1, 2)).size()
              << "voisins." << std::endl;

    s.stabil();
    std::ofstream f("stab_8x8_5.txt");
    f << s;
    f << s.nb_total_eboul();
    f.close();

    // question 14
    Sandpile t(100, 100);

    t.stabil();
    std::cout << s.nb_total_eboul() << " éboulements" << std::endl;
    std::cout << t << std::endl;

    // question 16
    std::mt19937_64 g(time(nullptr));
    t.add_random_grain(g, 3);

    // question 20
    Sandpile u(3, 2);
    u.stabil();
    Sandpile w(u);
    for (int n = 1; n < 2415; ++n) {
        w = w + u;
    }
    std::cout << "L'élément neutre pour le terrai 3x2 est :\n";
    std::cout << w;

    // question 21
    Sandpile v(3, 2, {{{2, 1}, 3}});
    std::cout << "La configuration v vaut :\n" << v;
    return 0;
}
