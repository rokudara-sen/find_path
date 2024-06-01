#include "../include/dijkstra.h"
#include <limits>
#include <queue>
#include <algorithm>

Dijkstra::Dijkstra(Graph* graph) {
    this->graph = graph;
}

void Dijkstra::find_shortest_path(int start, int goal)
{
    int num_stations = graph->get_stations().size();
    distances.resize(num_stations, std::numeric_limits<int>::max());
    previous.resize(num_stations, -1);
    std::vector<bool> visited(num_stations, false);

    initialize(start);

    for (int i = 0; i < num_stations; i++)
    {
        int u = get_min_distance_vertex(visited);
        if(u == -1)
            break;
        visited[u] = true;

        for(const Edge& edge : graph->get_stations()[u].edges)
        {
            int v = edge.destination;
            int weight = edge.cost;
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
    std::vector<int> path;
    for(int at = goal; at != -1; at = previous[at])
    {
        path.push_back(at);
    }
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

void Dijkstra::initialize(int start)
{
    distances[start] = 0;
}

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
