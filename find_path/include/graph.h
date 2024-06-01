#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

struct Edge
{
    int destination;
    int cost;
};

struct Station
{
    std::string name;
    std::vector<Edge> edges;
};

class Graph
{
public:
    Graph(const std::string& filename);
    virtual ~Graph() = default;
    int get_station_index(const std::string& name);
    std::string get_station_name(int index);
    const std::vector<Station>& get_stations() const;
private:
    std::vector<Station> stations;
    void load_from_file(const std::string& filename);
};