#pragma once
#include <vector>
#include <string>

#include "Continent.h"
#include "Country.h"

using namespace std;

class Map {
private:
    vector<Continent*> continents;
    vector<Country*> countries;

public:
    Map();
    vector<Country*> get_countries();
    vector<Continent*> get_continents();
    void add_country(Country* new_country);
    void add_continent(Continent* new_continent);
    bool validate();
    bool validate_unique_continents() const;
};
