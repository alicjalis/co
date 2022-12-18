#ifndef GRAPH_COLORING_GRAPH
#define GRAPH_COLORING_GRAPH

#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

#include "utility.hpp"

namespace ig {

    class graph {

        std::vector<std::pair<int, int>> e_list;
        std::vector<std::vector<int>> adj_list;
        std::vector<std::vector<bool>> adj_matrix;
        size_t m_size;

        // Przejście DFS, dla każdego wierzchołka, do którego
        // udało mu się pójść, zapisuje true w tablicy visited
        void traverse(int u, bool visited[]) const {
            visited[u] = true;
            for (int v = 0; v < m_size; v++) {
                if (adj_matrix[u][v] and !visited[v]) traverse(v, visited); // zaznacza gdzie udalo mu sie pojsc
            }
        }

    public:

        explicit graph(size_t size) {
            this->m_size = size;
            adj_list = std::vector<std::vector<int>>(size);
            adj_matrix = std::vector<std::vector<bool>>(size, std::vector<bool>(size, false));
        }

        graph(size_t size, std::vector<std::pair<int, int>> edges_list) {

            this->m_size = size;
            this->e_list = std::move(edges_list);

            // Tworzenie listy somsiedztwa
            adj_list = std::vector<std::vector<int>>(size);
            for (const std::pair<int, int>& edge: this->e_list) {
                adj_list[edge.first].push_back(edge.second);
                adj_list[edge.second].push_back(edge.first);
            }

            // Tworzenie macierzy somsiedztwa
            adj_matrix = std::vector<std::vector<bool>>(size, std::vector<bool>(size, false));
            for (const std::pair<int, int>& edge: this->e_list) {
                adj_matrix[edge.first][edge.second] = true;
                adj_matrix[edge.second][edge.first] = true;
            }
        }

        explicit graph(const std::string& file_name) {
            std::vector<std::pair<int, int>> edges = load_edges(file_name);
            int max_v_index = 0;
            for (const auto& edge: edges) max_v_index = std::max(max_v_index, std::max(edge.first, edge.second));
            *this = graph(max_v_index + 1, edges);
        }

        void generate_random(float fill) {
            std::vector<std::pair<int, int>> edges;
            for (int i = 0; i < m_size - 1; i++) {
                for (int j = i + 1; j < m_size; j++) {
                    bool add_this_edge = ig::random_bool(fill);
                    if (add_this_edge) {
                        std::pair<int, int> edge = {i, j};
                        edges.push_back(edge); // dodanie pary na koniec wektora
                    }
                }
            }
            *this = graph(m_size, edges);
        }

        // Funkcja oznaczona adnotacją [[nodiscard]] zwraca wynik, którego powinno
        // się nie ignorować, bo funkcja ta nie robi nic więcej poza obliczaniem go
        // graph.is_connected(); // NIEFAJNIE
        // bool connected = graph.is_connected(); // FAJNIE
        // if (graph.is_connected()) {} // FAJNIE
        [[nodiscard]] bool is_connected() const {
            bool visited[m_size];
            for (int i = 0; i < m_size; i++) visited[i] = false;
            traverse(0, visited);
            // Jeśli DFSowi nie udało się odwiedzić wszystkich wierzchołków, to graf nie jest spójny
            for (int i = 0; i < m_size; i++) if (!visited[i]) return false;
            return true;
        }

        [[nodiscard]] size_t size() const {
            return m_size;
        }

        [[nodiscard]] const std::vector<std::vector<int>>& adjacency_list() const {
            return adj_list;
        }

        void print_adjacency_list() const {
            for (int vertex = 0; vertex < m_size; vertex++) {
                std::cout << vertex << ". ";
                for (int neighbor: adj_list[vertex]) std::cout << neighbor << " ";
                std::cout << "\n";
            }
        }

        void print_edges_list() const {
            for (const auto& edge: e_list) std::cout << edge.first << " " << edge.second << "\n";
        }

        void print_edges_list(const std::string& file_name) const {
            std::ofstream output(file_name);
            output << size() << "\n";
            for (const auto& edge: e_list) output << edge.first << " " << edge.second << "\n";
            output.close();
        }
    };

}

#endif //GRAPH_COLORING_GRAPH
