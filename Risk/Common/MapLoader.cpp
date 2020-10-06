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
void MapLoader::parse(string file_name) {
        Map map;
        loaded_map = &map;

        ifstream file_reader(file_name);
        string line;

        if (file_reader.fail()) {
            throw runtime_error("Error opening or reading file: " + file_name);
        } else {
            /* CONTINENTS */
            // Skip file contents until we reach the continent section of the file
            while (getline(file_reader, line) &&  line !=  "[continents]") {}

            // Iterate and process each line defined under [continents]
            while (getline(file_reader, line) &&  !line.empty()) {
                auto* new_continent = new Continent(line);
                this-> loaded_map-> add_continent(new_continent);

                // Debug - REMOVEME
                cout << *new_continent << endl;
            }

            /* COUNTRIES */
            // Skip file contents until we reach the continent section of the file
            while (getline(file_reader, line) &&  line !=  "[countries]") {}

            int country_index = 1;
            while (getline(file_reader, line) &&  !line.empty()) {
                auto* new_country = new Country(line);
                Continent* current_continent = map.get_continents()[new_country->get_continent_id() - 1];
                current_continent->add_country(new_country);
                new_country->set_continent(current_continent);

                // If the ID defined for the country doesn't match our accumulator, they are not in order from 1 to n
                if (new_country-> get_id() !=  country_index) {
                    cout << "\nERROR at: " << line << endl;
                    throw invalid_argument("Reason: Countries are not listed in order.");
                }

                this-> loaded_map-> add_country(new_country);

                country_index++;
                // Debug
                cout << *new_country << endl;
            }

            /* BORDERS */
            // Skip file contents until we reach the continent section of the file
            while (getline(file_reader, line) &&  line !=  "[borders]") {}

            vector<Country*> all_countries = map.get_countries();
            while (getline(file_reader, line) &&  !line.empty()) {
                const vector<string> split_string = split(line);
                Country* current = all_countries[stoi(split_string[0]) - 1];

                for (int i = 1; i < split_string.size(); i++ ) {
                    current-> add_bordering_country(all_countries[stoi(split_string[i]) - 1]);
                }

                // Debug - REMOVEME
                cout << "border data: " <<  line << endl;
            }

            // Debug - REMOVEME
            bool map_validate = map.validate();
            bool map_validate_unique_continents = map.validate_unique_continents();
            cout << "\nAll countries are linked IS VALID?: " << map_validate << endl;
            cout << "Each country belongs to one and only one continent IS VALID?: " << map_validate_unique_continents << endl;
        }
}

MapLoader::MapLoader() = default;
