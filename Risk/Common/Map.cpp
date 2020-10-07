#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <array>
#include <map>

#include "Map.h"

using namespace std;


/* Constructors */
Map::Map() = default;


/* Accessors & Mutators */
vector<Country *> Map::get_countries() {
    return countries;
}

vector<Continent *> Map::get_continents() {
    return continents;
}

/* Methods */
void Map::add_country(Country *new_country) {
    this->countries.push_back(new_country);
}

void Map::add_continent(Continent *new_continent) {
    this->continents.push_back(new_continent);
}

bool Map::verify_connected_subgraph() const {
    int total_countries = countries.size();
    int total_continents = continents.size();
    // Arrays to keep track of countries and continents that have been visited
    bool* visited_countries = new bool[total_countries];
    bool* visited_continents = new bool[total_continents];

    // Initialize all values to false besides our starting value
    for (int i = 0; i < total_countries; i++) {
        visited_countries[i] = (i == 0);

        if (i < total_continents) {
            visited_continents[i] = false;
        }
    }

    list<int> queue = { 0 };

    while (!queue.empty()) {
        // Get the current value at the front and then remove it from our queue
        int current = queue.front();
        queue.pop_front();

        Country *current_country = countries[current];

        // Get the border countries from the current country being traversed
        vector<Country *> bordering_countries = current_country->get_bordering_country();
        int bordering_count = current_country->get_bordering_country().size();

        // Mark continent as visited
        visited_continents[current_country->get_continent_id() - 1] = true;

        // Iterate through each bordering country
        for (int i = 0; i < bordering_count; i++) {
            Country *bordering_country = bordering_countries[i];

            // If the country wasn't already visited, process it
            if (!visited_countries[bordering_country->get_id() - 1]) {

                // Verify that the bordering country also has the current country as a border
                if (bordering_country->borders_country(current_country)) {
                    // Add it to the queue to be processed on following iterations
                    queue.push_back(bordering_country->get_id() - 1);
                    visited_countries[bordering_country->get_id() - 1] = true;
                } else {
                    // If the bordering country doesn't also have the current country as a border, return false (invalid)
                    return false;
                }
            }
        }
    }

    // Check that all countries and continents were marked as visited, if not return false
    for (int i = 0; i < total_countries; i++) {
        if (!visited_countries[i]) return false;

        if (i < total_continents) {
            if (!visited_continents[i]) return false;
        }
    }
    return true;
}

/**
 *
 * @return true or false
 */
bool Map::validate() const {
    return verify_connected_subgraph() && verify_unique_continents();
}

/**
 * Verify that each country has only a single continent
 * @return true or false
 */
bool Map::verify_unique_continents() const {
    map<string, string> country_continent;

    for (Continent* continent: continents) {
        for (Country* country: continent->get_countries()) {
            // Check that a key for the current country exists
            if(country_continent.count(country->get_name()) != 0) {
                return false;
            }
            country_continent[country->get_name()] = continent->get_name();
        }
    }
    return true;
}