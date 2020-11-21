#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "MapLoader.h"
#include "Util.h"

using namespace std;


/* Constructors */
MapLoader::MapLoader() = default;


/* Methods */
/**
 * Parses a .map file into a Map entity with continents and territories linked
 *
 * NOTE Spaces used to separate data in a line, can't be used in country/continent names
 * .map files broken into sections:
 *
 * Continents, delimited by [continents] - ORDER IS IMPORTANT, CONTINENT IDS BASED ON POSITION
 *  Continent_Name / Number of army_bonus / Color
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
Map *MapLoader::parse(string file_name, bool verbose) {
    Map *map = new Map();

    ifstream file_reader(file_name);
    string line;

    if (file_reader.fail()) {
        throw runtime_error("Error opening or reading file: " + file_name);
    } else {
        /* CONTINENTS */
        // Skip file contents until we reach the continent section of the file
        while (getline(file_reader, line) && line != "[continents]") {}
        if (file_reader.eof()) {
            throw invalid_argument("Error loading map -> Reason: Cannot find continents.");
        }

        // Iterate and process each line defined under [continents]
        while (getline(file_reader, line) && !line.empty()) {
            vector<string> split_string = split(line);

            // Verify that all data for territories in map file are available
            if (split_string.size() != 3) {
                throw invalid_argument("Error loading map -> Reason: Missing data for continent.");
            }
            for (const string &x: split_string) {
                if (x.empty()) {
                    throw invalid_argument("Error loading map -> Reason: Missing data for continent.");
                }
            }
            auto *new_continent = new Continent(line);
            map->add_continent(new_continent);
        }

        /* COUNTRIES */
        // Skip file contents until we reach the countries section of the file
        while (getline(file_reader, line) && line != "[countries]") {}
        if (file_reader.eof()) {
            throw invalid_argument("Error loading map -> Reason: Cannot find territories.");
        }

        // Iterate and process each line defined under [countries]
        int territory_index = 1;
        while (getline(file_reader, line) && !line.empty()) {
            vector<string> split_string = split(line);

            // Verify that all data for territories in map file are available
            if (split_string.size() != 5) {
                throw invalid_argument("Error loading map -> Reason: Missing data for territory.");
            }
            for (const string &x: split_string) {
                if (x.empty()) {
                    throw invalid_argument("Error loading map -> Reason: Missing data for territory.");
                }
            }

            auto *new_territory = new Territory(line);

            // Verify that the continent id is valid
            if (new_territory->get_continent_id() > map->get_continents().size()) {
                throw invalid_argument("Error loading map -> Reason: Territory with invalid continent id.");
            }

            Continent *current_continent = map->get_continents()[new_territory->get_continent_id() - 1];
            current_continent->add_territory(new_territory);
            new_territory->set_continent(current_continent);

            // If the ID defined for the territory doesn't match our accumulator, they are not in order from 1 to n
            if (new_territory->get_id() != territory_index) {
                throw invalid_argument("Error loading map -> Reason: Territories are not listed in order.");
            }

            map->add_territory(new_territory);

            territory_index++;
        }

        /* BORDERS */
        // Skip file contents until we reach the continent section of the file
        while (getline(file_reader, line) && line != "[borders]") {}
        if (file_reader.eof()) {
            throw invalid_argument("Error loading map -> Reason: Cannot find borders.");
        }

        // Iterate and process each line defined under [borders]
        vector<Territory *> all_territories = map->get_territories();
        while (getline(file_reader, line) && !line.empty()) {
            const vector<string> split_string = split(line);

            // Verify that borders in map file per country exist
            if (split_string.size() < 2) {
                throw invalid_argument(
                        "Error loading map -> Reason: Territory is missing its borders or territory id is missing.");
            }
            for (const string &x: split_string) {
                if (x.empty()) {
                    throw invalid_argument(
                            "Error loading map -> Reason: Territory is missing its borders or territory id is missing.");
                }
            }

            // Verify that the territory id actually exists
            const int territory_id = stoi(split_string[0]);
            if (territory_id > all_territories.size()) {
                throw invalid_argument("Error loading map -> Reason: Initial territory index out of range.");
            }

            Territory *current = all_territories[territory_id - 1];

            for (int i = 1; i < split_string.size(); i++) {
                const int bordering_territory_id = stoi(split_string[i]);
                if (bordering_territory_id > all_territories.size()) {
                    throw invalid_argument("Error loading map -> Reason: Bordering territory id doesn't exist.");
                }

                current->add_bordering_territory(all_territories[stoi(split_string[i]) - 1]);
            }
        }
    }

    /* VALIDATION */
    // check if map is a connected graph
    if (map->verify_map_connected_graph()) {
        verbose && (cout << "Map is a connected graph." << endl);
    } else {
        throw invalid_argument("Error loading map -> Reason: Map is not a connected graph.");
    }
    // check if continents are a connected subgraph
    if (map->verify_continent_connected_subgraph()) {
        verbose && (cout << "Continents are connected subgraphs." << endl);
    } else {
        throw invalid_argument("Error loading map -> Reason: Continents are not connected subgraphs.");
    }
    // check if territories are connected by at most 1 continent
    if (map->verify_unique_continents()) {
        verbose && (cout << "Territories all have unique continents." << endl);
    } else {
        throw invalid_argument("Error loading map -> Reason: Territories do not have unique continents.");
    }

    // validated map object is returned
    return map;
}

/**
 * Parses conquest formatted map files
 *
 * @param file_name
 * @param verbose
 * @return
 */
Map *ConquestFileReader::parse(string file_name, bool verbose) {
    Map *map = new Map();

    ifstream file_reader(file_name);
    string line;

    if (file_reader.fail()) {
        throw runtime_error("Error opening or reading file: " + file_name);
    } else {
        /* CONTINENTS */
        // Skip file contents until we reach the continent section of the file
        while (getline(file_reader, line) && line != "[Continents]") {}
        if (file_reader.eof()) {
            throw invalid_argument("Error loading map -> Reason: Cannot find continents.");
        }

        // Keep track of continents created using a dictionary of it's name
        // (In domination files we had the luxury of ordering and IDs, here we have to use the string names)
        std::map<string, Continent *> continent_db;
        // Iterate and process each line defined under [continents]
        while (getline(file_reader, line) && !line.empty()) {
            // Each Continent line must have 2 elements
            // {Country Name}[0]={Army bonus}[1]
            vector<string> split_string = split(line, '=');

            // Verify that all data for territories in map file are available
            if (split_string.size() != 2) {
                throw invalid_argument("Error loading map -> Reason: Missing data for continent.");
            }

            for (const string &x: split_string) {
                if (x.empty()) {
                    throw invalid_argument("Error loading map -> Reason: Missing data for continent.");
                }
            }

            auto *new_continent = new Continent(split_string[0], stoi(split_string[1]));
            continent_db.insert({new_continent->get_name(), new_continent});
            map->add_continent(new_continent);
        }


        /* COUNTRIES */
        // Skip file contents until we reach the countries section of the file
        while (getline(file_reader, line) && line != "[Territories]") {}
        if (file_reader.eof()) {
            throw invalid_argument("Error loading map -> Reason: Cannot find territories.");
        }

        // Keep a dictionary of all territory names and their respective parent continent and bordering countries
        std::map<string, pair<Continent *, vector<string>>> territory_db;
        // Iterate and process each line defined under [Territories]
        while (getline(file_reader, line) && !line.empty()) {
            // {Territory Name}[0],{x coord}[1],{y coord}[2],{Parent Continent Name}[3], {Bordering Territory name}[4...N]
            vector<string> split_string = split(line, ',');

            string territory_name = split_string[0];

            // Check if the territory already exists in our map
            if (territory_db.count(territory_name)) {
                // Defining a territory twice
                if (territory_db.find(territory_name)->second.first != nullptr) {
                    // Dupe throw error
                } else {
                    Continent *parent_continent = continent_db.find(split_string[3])->second;
                    territory_db.find(territory_name)->second.first = parent_continent;
                }
            }

            // Add the territory and the pointer to its continent to the map using our continent continent_db
            territory_db.insert({
                                        territory_name,
                                        make_pair(continent_db.find(split_string[3])->second, vector<string>())
                                });

            // Iterate through all Bordering territories
            for (int i = 4; i < split_string.size(); i++) {
                // If the territory is new, handle it as a special case
                if (territory_db.count(split_string[i]) == 0) {
                    // Add the new territory to our map since it doesn't exist already
                    // (NOTE: It's possible for a territory to appear as a bordering country before it was defined on its own line)
                    territory_db.insert({
                                                split_string[i],
                                                make_pair(nullptr, vector<string>())
                                        });
                }

                // Add the bordering territory to the vector belonging to the parent
                territory_db.find(territory_name)->second.second.push_back(split_string[i]);
            }
        }

        int count = 0;
        std::map<string, Territory *> territory_ptr;
        // Using our constructed map of ("Territory Name" -> ["Bordering Territory Name"])
        // Construct a territory object for each Country that appeared as a key
        for (const auto &elem : territory_db) {
            if (elem.second.first == nullptr) {
                // ERROR!
                // A territory was marked as a bordering territory but never had its continent defined
                throw invalid_argument("Continent was not specified for Territory: " + elem.first);
            }

            Continent *current_continent = elem.second.first;
            auto *new_territory = new Territory(++count, elem.first, current_continent);
            // Add to the map object
            map->add_territory(new_territory);
            // Add to the continent object
            current_continent->add_territory(new_territory);
            // Add it to our map of initialized territories
            territory_ptr.insert({elem.first, new_territory});
        }

        // Iterate through all our defined territories and apply relevant borders

        // Iterate through map of instantiated territories ("Territory Name" -> *Territory)
        for (const auto &elem : territory_db) {
            // Iterate through string vector of bordering territory names
            for (const auto &border : elem.second.second) {
                // Ensure that the territory instance was created
                if (territory_ptr.count(border)) {
                    territory_ptr.find(elem.first)->second->add_bordering_territory(
                            territory_ptr.find(border)->second
                    );
                } else {
                    // If a territory does not have a pointer, it means that it was not defined as it's own
                    // line in the map file, and therefor we don't have a Continent set for it
                    throw invalid_argument("Continent was not specified for Territory: " + elem.first);
                }
            }
        }

    }

    /* VALIDATION */
    // check if map is a connected graph
    if (map->verify_map_connected_graph()) {
        verbose && (cout << "Map is a connected graph." << endl);
    } else {
        throw invalid_argument("Error loading map -> Reason: Map is not a connected graph.");
    }
    // check if continents are a connected subgraph
    if (map->verify_continent_connected_subgraph()) {
        verbose && (cout << "Continents are connected subgraphs." << endl);
    } else {
        throw invalid_argument("Error loading map -> Reason: Continents are not connected subgraphs.");
    }
    // check if territories are connected by at most 1 continent
    if (map->verify_unique_continents()) {
        verbose && (cout << "Territories all have unique continents." << endl);
    } else {
        throw invalid_argument("Error loading map -> Reason: Territories do not have unique continents.");
    }

    return map;
}

Map *ConquestFileReaderAdapter::parse(string file_name, bool verbose) {
    return _adaptee->parse(file_name, verbose);
}
