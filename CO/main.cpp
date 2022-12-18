#include <iostream>

#include "graph_rep.h"
#include "greedy_alg.hpp"

int main() {

    const int k = 200;
    const float fill = 0.5;

//     Generowanie losowego grafu
//    ig::graph graph(k);
//    graph.generate_random(fill);
//    while (not graph.is_connected()) graph.generate_random(fill);

    // Wczytywanie grafu z pliku
    ig::graph graph("test8.txt");

    // Zapisywanie grafu do pliku
//    graph.print_edges_list("edges_list.txt");

    // Wypisywanie grafu do konsoli
    graph.print_edges_list();

//     Algorytm + liczenie czasu
    ig::timer<ig::precision_us> clock; // Tu możesz sobie zmienić na mierzenie w nanosekundach np.
    clock.start();
    ig::greedy_coloring(graph);
    clock.stop();
    std::cout << "time of execution: " << clock.get_measured_time() << "  " << clock.unit() << std::endl;

    return 0;
}