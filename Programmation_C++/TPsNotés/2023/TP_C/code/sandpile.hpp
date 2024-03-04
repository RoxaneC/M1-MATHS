#ifndef _SANDPILE_HPP
#define _SANDPILE_HPP

#include <iostream>
#include <list>
#include <map>
#include <random>
#include <vector>

using upair = std::pair<unsigned, unsigned>;

class Sandpile;

std::ostream &operator<<(std::ostream &, const Sandpile &);
Sandpile operator+(const Sandpile &, const Sandpile &);

class Sandpile {
  private:
    unsigned m;
    unsigned n;

    std::vector<unsigned> terrain; // (i,j) <-> i+m*j
    std::vector<unsigned> nb_eboul;
    std::list<upair> next_eboul;

    void incr_et_test(const upair &);

  public:
    // constructeurs
    Sandpile(unsigned m_, unsigned n_, unsigned k = 4);
    Sandpile(unsigned m_, unsigned n_, const std::map<upair, unsigned> &);

    // accesseurs
    unsigned h(const upair &p) const {
        return terrain[p.first + m * p.second];
    }
    unsigned operator()(unsigned i, unsigned j) const {
        return terrain[i + m * j];
    }

    // mutateur
    unsigned &h(const upair &p) {
        return terrain[p.first + m * p.second];
    }

    std::list<upair> voisins(const upair &p) const;

    // opérations sur les configurations
    void eboul(const upair &p);
    unsigned stabil();

    unsigned nb_total_eboul() const;
    unsigned volume_total() const;
    bool instable(const upair &p) const {
        return h(p) >= 4;
    }
    bool instable(unsigned i, unsigned j) const {
        return instable(upair(i, j));
    }
    bool coord_valable(const upair &p) const;

    unsigned add_random_grain(std::mt19937_64 &g, unsigned k = 1);

    // affichage et somme
    friend std::ostream &operator<<(std::ostream &, const Sandpile &);
    friend Sandpile operator+(const Sandpile &, const Sandpile &);
};

#endif
