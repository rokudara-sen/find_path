#include <iostream>

#include "../include/dijkstra.h"
#include "../include/graph.h"

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        std::cerr << "Usage: " << argv[0] << " filename_graph start_station goal_station\n";
        return 1;
    }

    std::string filename = argv[1];
    std::string start_station = argv[2];
    std::string goal_station = argv[3];

    Graph graph(filename);

    int start_index = graph.get_station_index(start_station);
    int goal_index = graph.get_station_index(goal_station);

    if(start_index == -1 || goal_index == -1)
    {
        std::cerr << "Invalid start or goal station.\n";
        return 1;
    }

    Dijkstra dijkstra(&graph);
    dijkstra.find_shortest_path(start_index, goal_index);
    dijkstra.print_path(start_index, goal_index);
    
    return 0;
}
