#include "../include/graph.h"

#include <iomanip>

Graph::Graph(const std::string& filename)
{
    load_from_file((filename)); // lade von datei
}

int Graph::get_station_index(const std::string& name)
{
    // Schleife durch alle stationen
    for(size_t i = 0; i < stations.size(); ++i)
    {
        // wenn station name übereinstimmt, gib index zurück
        if(stations[i].name == name)
        {
            return i;
        }
    }
    // wenn keine übereinstimmung gefunden, gib -1 zurück
    return -1;
}

std::string Graph::get_station_name(int index)
{
    // wenn index im bereich, gib station name zurück
    if(index >= 0 && index < stations.size())
    {
        return stations[index].name;
    }
    // wenn index außerhalb des bereichs, gib leeren string zurück
    return "";
}

const std::vector<Station>& Graph::get_stations() const
{
    // gib alle stationen zurück
    return stations;
}

void Graph::load_from_file(const std::string& filename)
{
    std::ifstream file(filename); // öffne datei
    if(!file.is_open())
    {
        // wenn datei nicht geöffnet werden kann, gib fehler aus
        std::cerr << "Konnte datei nicht öffnen: " << filename << "\n";
        return;
    }

    // durchlauf jede zeile in der datei
    std::string line;
    while(getline(file, line))
    {
        std::stringstream ss(line);
        std::string line_name;
        getline(ss, line_name, ':');

        std::string station_name;
        int cost;
        std::vector<std::string> station_names;
        std::vector<int> costs;

        // lies station namen und kosten und füge sie zu den listen hinzu
        while(ss >> std::quoted(station_name) >> cost)
        {
            station_names.push_back(station_name);
            costs.push_back(cost);
        }

        // durchlauf alle station namen
        for(size_t i = 0; i < station_names.size(); ++i)
        {
            int station_index = get_station_index(station_names[i]);
            // wenn station nicht existiert, erstelle neue und füge sie zur liste hinzu
            if(station_index == -1)
            {
                stations.push_back({station_names[i]});
                station_index = stations.size() - 1;
            }

            // wenn es noch eine nächste station gibt, verbinde aktuelle station mit der nächsten
            if(i < station_names.size() - 1)
            {
                int next_station_index = get_station_index(station_names[i + 1]);
                if(next_station_index == - 1)
                {
                    stations.push_back({station_names[i + 1]});
                    next_station_index = stations.size() - 1;
                }

                // füge kante zu nächster station hinzu
                stations[station_index].edges.push_back({next_station_index, costs[i]});
            }
        }
    }
    // nachdem alle zeilen verarbeitet wurden, erstelle rückwärtsverbindungen
    for(auto& station: stations) {
        for(auto& edge : station.edges) {
            // füge zu jeder kante eine rückwärtskante hinzu
            stations[edge.destination].edges.push_back({get_station_index(station.name), edge.cost});
        }
    }
}