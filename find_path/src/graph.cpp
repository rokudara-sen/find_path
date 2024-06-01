#include "../include/graph.h"

#include <iomanip>

Graph::Graph(const std::string& filename)
{
    load_from_file((filename));
}

int Graph::get_station_index(const std::string& name)
{
    for(size_t i = 0; i < stations.size(); ++i)
    {
        if(stations[i].name == name)
        {
            return i;
        }
    }
    return -1;
}

std::string Graph::get_station_name(int index)
{
    if(index >= 0 && index < stations.size())
    {
        return stations[index].name;
    }
    return "";
}

const std::vector<Station>& Graph::get_stations() const
{
    return stations;
}

void Graph::load_from_file(const std::string& filename)
{
    std::ifstream file(filename);
    if(!file.is_open())
    {
        std::cerr << "Unable to open file: " << filename << "\n";
        return;
    }

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

        while(ss >> std::quoted(station_name) >> cost)
        {
            station_names.push_back(station_name);
            costs.push_back(cost);
        }

        for(size_t i = 0; i < station_names.size(); ++i)
        {
            int station_index = get_station_index(station_names[i]);
            if(station_index == -1)
            {
                stations.push_back({station_names[i]});
                station_index = stations.size() - 1;
            }

            if(i < station_names.size() - 1)
            {
                int next_station_index = get_station_index(station_names[i + 1]);
                if(next_station_index == - 1)
                {
                    stations.push_back({station_names[i + 1]});
                    next_station_index = stations.size() - 1;
                }
                stations[station_index].edges.push_back({next_station_index, costs[i]});
                stations[next_station_index].edges.push_back({station_index, costs[i]});
            }
        }
    }
}
