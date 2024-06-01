#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph.h"
#include <vector>

class Dijkstra {
public:
    Dijkstra(Graph* graph);
    void find_shortest_path(int start, int goal);
    void print_path(int start, int goal);

private:
    Graph* graph;
    std::vector<int> distances;
    std::vector<int> previous;
    void initialize(int start);
    int get_min_distance_vertex(const std::vector<bool>& visited);
};

#endif
