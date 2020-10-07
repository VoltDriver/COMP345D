#pragma once
#include <vector>
#include <string>

#include "Continent.h"
#include "Territory.h"

using namespace std;

class Map {
private:
    vector<Continent*> continents;
    vector<Territory*> territories;

public:
    Map();
    vector<Territory*> get_territories();
    vector<Continent*> get_continents();
    void add_territory(Territory* new_territory);
    void add_continent(Continent* new_continent);
    bool validate() const;
    bool verify_map_connected_subgraph() const;
    bool verify_continent_connected_subgraph() const;
    bool verify_unique_continents() const;
    void print(std::vector <Territory> const &a);
};
