#include "sandpile.hpp"
#include <algorithm>
#include <numeric> // pour std::accumulate

Sandpile::Sandpile(unsigned m0, unsigned n0, unsigned k)
    : m(m0), n(n0), terrain(m0 * n0, k), nb_eboul(m0 * n0) {
    if (k >= 4) {
        for (unsigned i = 0; i < m; ++i) {
            for (unsigned j = 0; j < n; ++j) {
                next_eboul.push_back(upair(i, j));
            }
        }
    }
}

Sandpile::Sandpile(unsigned m0, unsigned n0,
                   const std::map<upair, unsigned> &data)
    : m(m0), n(n0), terrain(m0 * n0), nb_eboul(m0 * n0) {
    for (auto p = data.begin(); p != data.end(); ++p) {
        // le type complet de p est std::map<upair, unsigned>::const_iterator
        if (coord_valable(p->first)) {
            h(p->first) = p->second;
            if (p->second >= 4) {
                next_eboul.push_back(p->first);
            }
        }
    }
}

bool Sandpile::coord_valable(const upair &p) const {
    unsigned i = p.first;
    unsigned j = p.second;
    return (i < m) && (j < n);
}

std::list<upair> Sandpile::voisins(const upair &p) const {
    unsigned i = p.first;
    unsigned j = p.second;
    std::list<upair> l;
    if (i > 0) {
        l.push_back(upair(i - 1, j));
    }
    if (i < m - 1) {
        l.push_back(upair(i + 1, j));
    }
    if (j > 0) {
        l.push_back(upair(i, j - 1));
    }
    if (j < n - 1) {
        l.push_back(upair(i, j + 1));
    }
    return l;
}

void Sandpile::eboul(const upair &p) {
    if (h(p) >= 4) {
        h(p) -= 4;
        std::list<upair> vois = voisins(p);
        nb_eboul[p.first + m * p.second] += 1;
        for (const upair &v : vois) {
            incr_et_test(v);
        }
        /* ou
        for(std::list<upair>::const_iterator it = vois.begin(); it !=
        vois.end();
        ++it) { incr_et_test(*v);
        }
        ou bien
        std::for_each(vois.begin(), vois.end(), [this](const upair & p)
        {incr_and_test(p);});"
        */
    }
    return;
}

void Sandpile::incr_et_test(const upair &p) {
    ++h(p);
    if (h(p) >= 4) {
        next_eboul.push_back(p);
    }
    return;
}

unsigned Sandpile::stabil() {
    int t_avalanche(0);
    while (!next_eboul.empty()) {
        upair p = next_eboul.front();
        next_eboul.pop_front();
        eboul(p);
        ++t_avalanche;
    }
    return t_avalanche;
}

std::ostream &operator<<(std::ostream &o, const Sandpile &s) {
    std::string chars = ".oO0";
    std::vector<std::string> color_codes{"\x1B[31m", "\x1B[32m", "\x1B[33m",
                                         "\x1B[34m"};
    std::string normal = "\x1B[0m";
    for (unsigned j = 0; j < s.n; ++j) {
        for (unsigned i = 0; i < s.m; ++i) {
            if (s(i, j) < 4) {
                o << color_codes[s(i, j)] << chars[s(i, j)] << normal;
            } else {
                o << s(i, j);
            }
        }
        o << std::endl;
    }
    o << std::endl;
    return o;
}

Sandpile operator+(const Sandpile &s, const Sandpile &t) {
    unsigned m = std::min(s.m, t.m);
    unsigned n = std::min(s.n, t.n);
    Sandpile u(m, n, 0);
    for (unsigned i = 0; i < m; ++i) {
        for (unsigned j = 0; j < n; ++j) {
            u.terrain[i + m * j] =
                s.terrain[i + s.m * j] + t.terrain[i + t.m * j];
            if (u.instable(i, j)) {
                u.next_eboul.push_back(upair(i, j));
            }
        }
    }
    u.stabil();
    return u;
}

unsigned Sandpile::nb_total_eboul() const {
    return std::accumulate(nb_eboul.begin(), nb_eboul.end(), 0);
}

unsigned Sandpile::volume_total() const {
    return std::accumulate(terrain.begin(), terrain.end(), 0);
}

unsigned Sandpile::add_random_grain(std::mt19937_64 &g, unsigned k) {
    std::uniform_real_distribution<> u(n * m);
    for (unsigned i = 0; i < k; ++i) {
        ++terrain[u(g)];
    }
    return stabil();
}
