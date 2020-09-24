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
    static void validate();
    void add_country(Country*);
    void add_continent(Continent*);
};
