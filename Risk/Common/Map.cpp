#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <array>
#include <algorithm>

#include "Map.h"
#include "Util.h"

using namespace std;


// ######   #######  ##    ## ######## #### ##    ## ######## ##    ## ########
//##    ## ##     ## ###   ##    ##     ##  ###   ## ##       ###   ##    ##
//##       ##     ## ####  ##    ##     ##  ####  ## ##       ####  ##    ##
//##       ##     ## ## ## ##    ##     ##  ## ## ## ######   ## ## ##    ##
//##       ##     ## ##  ####    ##     ##  ##  #### ##       ##  ####    ##
//##    ## ##     ## ##   ###    ##     ##  ##   ### ##       ##   ###    ##
// ######   #######  ##    ##    ##    #### ##    ## ######## ##    ##    ##


/* Constructors */
// parameterized constructor
Continent::Continent(string &raw_continent) {
    const vector<string> continent_data = split(raw_continent);
    name = continent_data.at(0);
}

// copy constructor
Continent::Continent(const Continent &c) {
    this->name = *(new string(c.name));
    this->territories = c.territories;
    this->army_bonus = *(new int(c.army_bonus));
}

/* Accessors & Mutators */
string Continent::get_name() const {
    return name;
}

vector<Territory *> Continent::get_territories() const {
    return territories;
}

/* Methods */
void Continent::add_territory(Territory *territory) {
    territories.push_back(territory);
}

/* Overloaders */
// stream insertion operator
ostream &operator<<(std::ostream& strm, const Continent &continent) {
    return strm << "Continent("
                << "name: " << continent.name
                << ")";
}
// assignment operator
Continent& Continent::operator=(const Continent& c) {
    for (Territory *territory: territories) {
        delete territory;
    }
    this->name = *(new string(c.name));
    this->territories = c.territories;
    this->army_bonus = *(new int(c.army_bonus));

    return *this;
}


//######## ######## ########  ########  #### ########  #######  ########  ##    ##
//   ##    ##       ##     ## ##     ##  ##     ##    ##     ## ##     ##  ##  ##
//   ##    ##       ##     ## ##     ##  ##     ##    ##     ## ##     ##   ####
//   ##    ######   ########  ########   ##     ##    ##     ## ########     ##
//   ##    ##       ##   ##   ##   ##    ##     ##    ##     ## ##   ##      ##
//   ##    ##       ##    ##  ##    ##   ##     ##    ##     ## ##    ##     ##
//   ##    ######## ##     ## ##     ## ####    ##     #######  ##     ##    ##

/* Constructors */
// parameterized constructor
Territory::Territory(int id, string name, int continent) {
    this->id = id;
    this->name = name;
    this->continent_id = continent;
}

// parameterized constructor
Territory::Territory(string &raw_territory) {
    const vector<string> territory_data = split(raw_territory);
    this->id = std::stoi(territory_data.at(0));
    this->name = territory_data.at(1);
    this->continent_id = std::stoi(territory_data.at(2));
}

// copy constructor
Territory::Territory(const Territory &c) {
    this->id = *(new int(c.id));
    this->name = *(new string(c.name));
    this->continent_id = *(new int(c.continent_id));
    this->bordering_territories = c.bordering_territories;
    this->continent = new Continent(*c.continent);
}

/* Accessors & Mutators */
string Territory::get_name() const {
    return name;
}

int Territory::get_id() const {
    return id;
}

int Territory::get_continent_id() const {
    return continent_id;
}

void Territory::set_continent(Continent *continent) {
    this->continent = continent;
}

Continent *Territory::get_continent() const {
    return continent;
}

vector<Territory *> Territory::get_bordering_territory() {
    return this->bordering_territories;
}

/* Methods */
void Territory::add_bordering_territory(Territory *territory) {
    bordering_territories.push_back(territory);
}

string Territory::bordering_territories_tostring() const {
    string territory_list = "(";
    for (Territory *territory: bordering_territories) {
        territory_list += territory->get_name();

        if (territory != bordering_territories.back()) {
            territory_list += ", ";
        }
    }

    territory_list += ")";
    return territory_list;
}

bool Territory::borders_territory(Territory *comparator) const {
    return std::any_of(
            bordering_territories.begin(),
            bordering_territories.end(),
            [&](const Territory *bordering_territory) { return bordering_territory == comparator; });
}

/* Overloaders */
// stream insertion operator
ostream &operator<<(std::ostream &strm, const Territory &territory) {
    return strm << "Territory("
                << "id: " << territory.id << ", "
                << "name: " << territory.name << ", "
                << "continent: " << territory.continent->get_name() << ", "
                << "borders: " << territory.bordering_territories_tostring()
                << ")";
}
// assignment operator
Territory& Territory::operator=(const Territory& c) {
    for (Territory *border: bordering_territories) {
        delete border;
    }

    this->id = *(new int(c.id));
    this->name = *(new string(c.name));
    this->continent_id = *(new int(c.continent_id));
    this->bordering_territories = c.bordering_territories;

    return *this;
}


//##     ##    ###    ########
//###   ###   ## ##   ##     ##
//#### ####  ##   ##  ##     ##
//## ### ## ##     ## ########
//##     ## ######### ##
//##     ## ##     ## ##
//##     ## ##     ## ##

/* Constructors */


/* Destructor */
Map::~Map() {
    // deletes all territory objects stored on heap.
    for (Territory *territory: territories) {
        delete territory;
    }

    for (Continent *continent: continents) {
        delete continent;
    }
}

/* Accessors & Mutators */
vector<Territory *> Map::get_territories() {
    return territories;
}

vector<Continent *> Map::get_continents() {
    return continents;
}

/* Methods */
void Map::add_territory(Territory *new_territory) {
    this->territories.push_back(new_territory);
}

void Map::add_continent(Continent *new_continent) {
    this->continents.push_back(new_continent);
}

/**
 * Check that the entire map is a connected subgraph.
 * Traverse each territory and its borders and check that every node has been visited by the end.
 */
bool Map::verify_map_connected_graph() const {
    int total_territories = territories.size();
    // Arrays to keep track of territories and continents that have been visited
    bool* visited_territories = new bool[total_territories];

    // Initialize all values to false besides our starting value
    for (int i = 0; i < total_territories; i++) {
        visited_territories[i] = (i == 0);
    }

    list<int> queue = { 0 };

    while (!queue.empty()) {
        // Get the current value at the front and then remove it from our queue
        int current = queue.front();
        queue.pop_front();

        Territory *current_territory = territories[current];

        // Get the border territories from the current territory being traversed
        vector<Territory *> bordering_territories = current_territory->get_bordering_territory();
        int bordering_count = current_territory->get_bordering_territory().size();

        // Iterate through each bordering territory
        for (int i = 0; i < bordering_count; i++) {
            Territory *bordering_territory = bordering_territories[i];

            // If the territory wasn't already visited, process it
            if (!visited_territories[bordering_territory->get_id() - 1]) {

                // Verify that the bordering territory also has the current territory as a border
                if (bordering_territory->borders_territory(current_territory)) {
                    // Add it to the queue to be processed on following iterations
                    queue.push_back(bordering_territory->get_id() - 1);
                    visited_territories[bordering_territory->get_id() - 1] = true;
                } else {
                    // If the bordering territory doesn't also have the current territory as a border, return false (invalid)
                    return false;
                }
            }
        }
    }

    // Check that all territories and continents were marked as visited, if not return false
    for (int i = 0; i < total_territories; i++) {
        if (!visited_territories[i]) return false;
    }

    return true;
}

/**
 * Validates if map is a connected graph, continents are a connected subgraph and that continents are unique.
 * @return true or false
 */
bool Map::validate() const {
    return verify_map_connected_graph() && verify_unique_continents() && verify_continent_connected_subgraph();
}

/**
 * Check that each continent is a connected subgraph
 * Functionally equivalent to verify_map_connected_graph(), except we treat each continent
 * and its territories as its own map.
 */
bool Map::verify_continent_connected_subgraph() const {
    for (Continent *continent: continents) {
        vector<Territory*> continent_territories = continent->get_territories();

        // If the continent has no territories it is unreachable
        if (continent_territories.empty()) {
            return false;
        }

        // Iterate through each territory belonging to the continent
        for (Territory *_: continent_territories) {
            map<int, bool> visited_territories;

            // Initialize each territory to false in our map
            for (Territory *territory: continent_territories) {
                visited_territories.insert({territory->get_id() - 1, false });
            }

            list<int> queue;
            queue.push_back(continent_territories[0]->get_id() - 1);

            while (!queue.empty()) {
                // Get the current value at the front and then remove it from our queue
                int current = queue.front();
                queue.pop_front();

                Territory *current_territory = territories[current];

                // Get the border territories from the current territory being traversed
                vector<Territory *> bordering_territories = current_territory->get_bordering_territory();
                int bordering_count = current_territory->get_bordering_territory().size();

                // Iterate through each bordering territory
                for (int j = 0; j < bordering_count; j++) {
                    Territory *bordering_territory = bordering_territories[j];

                    // If the territory wasn't already visited, process it
                    if (!visited_territories[bordering_territory->get_id() - 1]) {

                        // Verify that the bordering territory also has the current territory as a border
                        if (bordering_territory->borders_territory(current_territory)) {
                            // Add it to the queue to be processed on following iterations
                            queue.push_back(bordering_territory->get_id() - 1);
                            visited_territories[bordering_territory->get_id() - 1] = true;
                        } else {
                            // If the bordering territory doesn't also have the current territory as a border, return false (invalid)
                            return false;
                        }
                    }
                }
            }

            for (Territory *territory: continent_territories) {
                if (!visited_territories[territory->get_id() - 1]) return false;
            }
        }
    }

    return true;
}

/**
 * Verify that each territory has only a single continent
 * @return true or false
 */
bool Map::verify_unique_continents() const {
    map<string, string> territory_continent;

    for (Continent* continent: continents) {
        for (Territory* territory: continent->get_territories()) {
            // Check that a key for the current territory exists
            if(territory_continent.count(territory->get_name()) != 0) {
                return false;
            }
            territory_continent[territory->get_name()] = continent->get_name();
        }
    }
    return true;
}