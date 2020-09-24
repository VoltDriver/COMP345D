#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "Continent.h"
#include "MapLoader.h"
#include "Util.h"

using namespace std;

void MapLoader::parse(string fileName) {
    try {
        Map map;
        this-> loaded_map = &map;

        ifstream fileReader(fileName);
        string line;

        if (fileReader.fail()) {
            cout << "Error opening file" << endl;
        } else {
            /* CONTINENTS */
            // Skip file contents until we reach the continent section of the file
            while (getline(fileReader, line) &&  line !=  "[continents]") {}

            while (getline(fileReader, line) &&  !line.empty()) {
                auto* new_continent = new Continent(line);
                this-> loaded_map-> add_continent(new_continent);

                cout << *new_continent << endl;
            }

            /* COUNTRIES */
            // Skip file contents until we reach the continent section of the file
            while (getline(fileReader, line) &&  line !=  "[countries]") {}

            int country_index = 1;
            while (getline(fileReader, line) &&  !line.empty()) {
                auto* new_country = new Country(line);
                this-> loaded_map-> add_country(new_country);

                cout << *new_country << endl;
            }


            /* BORDERS */
            // Skip file contents until we reach the continent section of the file
            while (getline(fileReader, line) &&  line !=  "[borders]") {}

            while (getline(fileReader, line) &&  !line.empty()) {
                cout << "border data: " <<  line << endl;
            }
        }
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }
}

MapLoader::MapLoader() = default;
