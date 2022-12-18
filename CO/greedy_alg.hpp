#ifndef CO_GREEDY_ALG_HPP
#define CO_GREEDY_ALG_HPP

#include <list>
#include <utility>

#include "graph_rep.h"

namespace ig {

    void greedy_coloring(const graph& graph) {

        size_t V = graph.size();
        const std::vector<std::vector<int>>& adj = graph.adjacency_list();
        int result[V];

        // dodanie pierwszego koloru do pierwszego wierzchołka
        result[0] = 0;

        // reszta wierzchołków nie ma kolorów
        for (int u = 1; u < V; u++)
            result[u] = -1;  // no color is assigned to u

        // Tablica do przechowywania dostępnych kolorów (tymczasowa). Wartość true
        // dla [cr] oznacza ze cr jest juz przydzielony do sasiednich wierzchołków
        bool available[V];
        for (int cr = 0; cr < V; cr++)
            available[cr] = false;

        // Przydział kolorów do reszty v-1 wierzchołków
        for (int u = 1; u < V; u++) {
            // przejdz przez sasiednie wierzchołki i oznacz ich kolory jako niedostepne
            for (int neighbor: adj[u]) if (result[neighbor] != -1) available[result[neighbor]] = true;

            // znajdź pierwszy dostępny kolor
            int cr;
            for (cr = 0; cr < V; cr++) if (not available[cr]) break;

            result[u] = cr; // przydziel znaleziony kolor

            // przywroc wszystkim wartosciom false dla kolejnej iteracji
            for (int neighbor: adj[u]) if (result[neighbor] != -1) available[result[neighbor]] = false;
        }

        int highest_color = 0;
        for (int u = 0; u < V; u++) {
            std::cout << "vertex " << u << " -> color " << result[u] << std::endl;
            highest_color = std::max(highest_color, result[u]);
        }
        std::cout << "number of colors: " << highest_color + 1 << std::endl;
    }
}

#endif //CO_GREEDY_ALG_HPP
