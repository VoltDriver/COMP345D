#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "Continent.h"
#include "MapLoader.h"
#include "Util.h"

using namespace std;

/**
 * Parses a .map file into a Map entity with continents and territories linked
 *
 * NOTE Spaces used to separate data in a line, can't be used in country/continent names
 * .map files broken into sections:
 *
 * Continents, delimited by [continents] - ORDER IS IMPORTANT, CONTINENT IDS BASED ON POSITION
 *  Continent_Name / Number of armies / Color
 *  EX: North_America 6 red
 *
 * Countries. delimited by [countries]
 * Id of the Territory (Needs to be in order) / Territory name / Id of the continent / X coords / Y coords
 * EX: 1 Alaska 1 44 83
 *
 * Borders, delimited by [borders]
 * Main country ID / Any number of bordering country IDs
 * EX: 1 2 3 38
 *
 * @param fileName Name of file to open
 */
Map MapLoader::parse(string file_name) {
        Map map;
        loaded_map = &map;

        ifstream file_reader(file_name);
        string line;

        if (file_reader.fail()) {
            throw runtime_error("Error opening or reading file: " + file_name);
        }
        else {
            /* CONTINENTS */
            // Skip file contents until we reach the continent section of the file
            while (getline(file_reader, line) &&  line !=  "[continents]") {}
            // if we reach end of file and have not found "[continents]", then there is an error
            if (file_reader.eof()) {
                throw invalid_argument("Error loading map -> Reason: Cannot find continents.");
            }

            // Iterate and process each line defined under [continents]
            while (getline(file_reader, line) &&  !line.empty()) {
                auto* new_continent = new Continent(line);
                this-> loaded_map-> add_continent(new_continent);
            }

            /* COUNTRIES */
            // Skip file contents until we reach the countries section of the file
            while (getline(file_reader, line) &&  line !=  "[countries]") {}
            // if we reach end of file and have not found "[countries]", then there is an error
            if (file_reader.eof()) {
                throw invalid_argument("Error loading map -> Reason: Cannot find territories.");
            }

            int territory_index = 1;
            while (getline(file_reader, line) &&  !line.empty()) {
                auto* new_territory = new Territory(line);

                // Verify that the continent id is valid
                if(new_territory->get_continent_id() > map.get_continents().size()) {
                    throw invalid_argument("Error loading map -> Reason: Territory with invalid continent id.");
                }

                Continent* current_continent = map.get_continents()[new_territory->get_continent_id() - 1];
                current_continent->add_territory(new_territory);
                new_territory->set_continent(current_continent);

                // If the ID defined for the territory doesn't match our accumulator, they are not in order from 1 to n
                if (new_territory-> get_id() != territory_index) {
                    throw invalid_argument("Error loading map -> Reason: Territories are not listed in order.");
                }

                this->loaded_map->add_territory(new_territory);

                territory_index++;
            }

            /* BORDERS */
            // Skip file contents until we reach the continent section of the file
            while (getline(file_reader, line) &&  line !=  "[borders]") {}
            // if we reach end of file and have not found "[borders]", then there is an error
            if (file_reader.eof()) {
                throw invalid_argument("Error loading map -> Reason: Cannot find borders.");
            }

            vector<Territory*> all_territories = map.get_territories();
            while (getline(file_reader, line) &&  !line.empty()) {
                const vector<string> split_string = split(line);

                // Verify that the territory id actually exists
                const int territory_id = stoi(split_string[0]);
                if (territory_id > all_territories.size()) {
                    throw invalid_argument("Initial territory index out of range");
                }

                Territory* current = all_territories[territory_id - 1];

                for (int i = 1; i < split_string.size(); i++ ) {
                    const int bordering_territory_id = stoi(split_string[i]);
                    if (bordering_territory_id > all_territories.size()) {
                        throw invalid_argument("Bordering territory id doesn't exist!");
                    }

                    current->add_bordering_territory(all_territories[stoi(split_string[i]) - 1]);
                }
            }
        }

        /* VALIDATION */
        // check if map is a connected graph
        if (map.verify_map_connected_graph()) {
            cout << "Map is a connected graph." << endl;
        }
        else {
            throw invalid_argument("Error loading map -> Reason: Map is not a connected graph.");
        }
        // check if continents are a connected subgraph
        if (map.verify_continent_connected_subgraph()) {
            cout << "Continents are connected subgraphs." << endl;
        }
        else {
            throw invalid_argument("Error loading map -> Reason: Continents are not connected subgraphs.");
        }
        // check if territories are connected by at most 1 continent
        if (map.verify_unique_continents()) {
            cout << "Territories all have unique continents." << endl;
        }
        else {
            throw invalid_argument("Error loading map -> Reason: Territories do not have unique continents.");
        }

        // validated map object is returned
        return *loaded_map;
}

MapLoader::MapLoader() = default;
