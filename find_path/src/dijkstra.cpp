#include "../include/dijkstra.h"
#include <limits>
#include <queue>
#include <algorithm>

// erstellt eine instanz von Dijkstra mit einem Graphen
Dijkstra::Dijkstra(Graph* graph) {
    this->graph = graph;
}

// findet den kürzesten weg vom start zum ziel
void Dijkstra::find_shortest_path(int start, int goal)
{
    // holt die anzahl der standorte
    int num_stations = graph->get_stations().size();
    
    // initialisiert die distanzen und den vorherigen knoten
    distances.resize(num_stations, std::numeric_limits<int>::max());
    previous.resize(num_stations, -1);
    
    // merkt sich, welche standorte besucht wurden
    std::vector<bool> visited(num_stations, false);

    // initialisiert den startknoten
    initialize(start);

    // geht durch alle standorte
    for (int i = 0; i < num_stations; i++)
    {
        // findet den standort mit der kleinsten distanz
        int u = get_min_distance_vertex(visited);
        
        // bricht ab, wenn kein knoten gefunden wurde
        if(u == -1)
            break;
        
        // markiert den standort als besucht
        visited[u] = true;

        // geht durch alle kanten vom aktuellen standort
        for(const Edge& edge : graph->get_stations()[u].edges)
        {
            // holt den nachbarstandort und die kosten der kante
            int v = edge.destination;
            int weight = edge.cost;
            
            // aktualisiert die distanz und den vorherigen knoten, wenn der nachbarstandort noch nicht besucht wurde
            // und die neue distanz kleiner ist
            if(!visited[v] && distances[u] + weight < distances[v])
            {
                distances[v] = distances[u] + weight;
                previous[v] = u;
            }
        }
    }
}

void Dijkstra::print_path(int start, int goal)
{
    // erstellt den weg von ziel zu start
    std::vector<int> path;
    for(int at = goal; at != -1; at = previous[at])
    {
        path.push_back(at);
    }
    
    // dreht den weg um
    std::reverse(path.begin(), path.end());

    std::cout << "Shortest path from " << graph->get_station_name(start) << " to " << graph->get_station_name(goal) << ":\n";
    for(int i = 0; i < path.size(); ++i)
    {
        std::cout << graph->get_station_name(path[i]);
        if(i < path.size() - 1)
        {
            std::cout << " -> ";
        }
    }
    std::cout << "\nTotal cost: " << distances[goal] << "\n";
}

// initialisiert den startknoten
void Dijkstra::initialize(int start)
{
    distances[start] = 0;
}

// holt den standort mit der kleinsten distanz, der noch nicht besucht wurde
int Dijkstra::get_min_distance_vertex(const std::vector<bool>& visited)
{
    int min = std::numeric_limits<int>::max();
    int min_index = -1;
    for(size_t i = 0; i < distances.size(); ++i)
    {
        if(!visited[i] && distances[i] < min)
        {
            min = distances[i];
            min_index = i;
        }
    }
    return min_index;
}
