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
 * Id of the Country (Needs to be in order) / Country name / Id of the continent / X coords / Y coords
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
            while (getline(file_reader, line) &&  line !=  "[continents]") {
//                throw invalid_argument("Error loading map -> Reason: Cannot find continents.");
            }

            // Iterate and process each line defined under [continents]
            while (getline(file_reader, line) &&  !line.empty()) {
                auto* new_continent = new Continent(line);
                this-> loaded_map-> add_continent(new_continent);
            }

            /* COUNTRIES */
            // Skip file contents until we reach the continent section of the file
            while (getline(file_reader, line) &&  line !=  "[countries]") {
//                throw invalid_argument("Error loading map -> Reason: Cannot find countries.");
            }

            int country_index = 1;
            while (getline(file_reader, line) &&  !line.empty()) {
                auto* new_country = new Country(line);

                // Verify that the continent id is valid
                if(new_country->get_continent_id() > map.get_continents().size()) {
                    throw invalid_argument("Error loading map -> Reason: Country with invalid continent id.");
                }

                Continent* current_continent = map.get_continents()[new_country->get_continent_id() - 1];
                current_continent->add_country(new_country);
                new_country->set_continent(current_continent);

                // If the ID defined for the country doesn't match our accumulator, they are not in order from 1 to n
                if (new_country-> get_id() !=  country_index) {
                    throw invalid_argument("Error loading map -> Reason: Countries are not listed in order.");
                }

                this->loaded_map->add_country(new_country);

                country_index++;
            }

            /* BORDERS */
            // Skip file contents until we reach the continent section of the file
            while (getline(file_reader, line) &&  line !=  "[borders]") {
//                throw invalid_argument("Error loading map -> Reason: Cannot find borders.");
            }

            vector<Country*> all_countries = map.get_countries();
            while (getline(file_reader, line) &&  !line.empty()) {
                const vector<string> split_string = split(line);

                // Verify that the country id actually exists
                const int country_id = stoi(split_string[0]);
                if (country_id > all_countries.size()) {
                    throw invalid_argument("Initial country index out of range");
                }

                Country* current = all_countries[country_id - 1];

                for (int i = 1; i < split_string.size(); i++ ) {
                    const int bordering_country_id = stoi(split_string[i]);
                    if (bordering_country_id > all_countries.size()) {
                        throw invalid_argument("Bordering country id doesn't exist!");
                    }

                    current-> add_bordering_country(all_countries[stoi(split_string[i]) - 1]);
                }
            }
        }

        if (map.verify_map_connected_subgraph()) {
            cout << "Map is a connected graph." << endl;
        }
        else {
            throw invalid_argument("Error loading map -> Reason: Map is not a connected graph.");
        }
        if (map.verify_continent_connected_subgraph()) {
            cout << "Continents are connected subgraphs." << endl;
        }
        else {
            throw invalid_argument("Error loading map -> Reason: Continents are not connected subgraphs.");
        }
        if (map.verify_unique_continents()) {
            cout << "Countries all have unique continents." << endl;
        }
        else {
            throw invalid_argument("Error loading map -> Reason: Countries do not have unique continents.");
        }
        return *loaded_map;
}

MapLoader::MapLoader() = default;
