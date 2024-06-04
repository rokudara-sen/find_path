#include <iostream>

#include "../include/dijkstra.h"
#include "../include/graph.h"

int main(int argc, char* argv[])
{
    // wenn die anzahl der argumente nicht 4 ist
    if (argc != 4)
    {
        // zeige wie das programm genutzt werden sollte
        std::cerr << "Usage: " << argv[0] << " filename_graph start_station goal_station\n";
        return 1;
    }

    // speichere die argumente in entsprechenden variablen
    std::string filename = argv[1];
    std::string start_station = argv[2];
    std::string goal_station = argv[3];

    // erstelle ein graph objekt mit dem angegebenen filename
    Graph graph(filename);

    // finde die indexe der start und ziel stationen
    int start_index = graph.get_station_index(start_station);
    int goal_index = graph.get_station_index(goal_station);

    // überprüfe ob die stationen existieren
    if(start_index == -1 || goal_index == -1)
    {
        std::cerr << "Invalid start or goal station.\n";
        return 1;
    }

    // erstelle ein dijkstra objekt und finde den kürzesten weg
    Dijkstra dijkstra(&graph);
    dijkstra.find_shortest_path(start_index, goal_index);
    // drucke den weg
    dijkstra.print_path(start_index, goal_index);
    
    return 0;
}
