#include <iostream>

#include "Map.h"

using namespace std;

/* Constructors */
Map::Map() = default;

/* Methods */
void Map::validate() {
    cout << "test" << endl;
}

void Map::add_country(Country* newCountry) {
    this-> countries.push_back(newCountry);
}

void Map::add_continent(Continent* newContinent) {
    this-> continents.push_back(newContinent);
}

