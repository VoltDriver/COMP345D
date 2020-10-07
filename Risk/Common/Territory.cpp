#include <ostream>
#include <algorithm>

#include "Territory.h"
#include "Util.h"


/* Constructors */
Territory::Territory(int id, string name, int continent) {
    this->id = id;
    this->name = name;
    this->continent_id = continent;
}

Territory::Territory(string &raw_territory) {
    const vector<string> territory_data = split(raw_territory);
    this->id = std::stoi(territory_data.at(0));
    this->name = territory_data.at(1);
    this->continent_id = std::stoi(territory_data.at(2));
}

Territory::Territory(const Territory &c) {
    this->id = *(new int(c.id));
    this->name = *(new string(c.name));
    this->continent_id = *(new int(c.continent_id));
    this->bordering_territories = c.bordering_territories;
    this->continent = c.continent;
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
ostream &operator<<(std::ostream &strm, const Territory &territory) {
    return strm << "Territory("
                << "id: " << territory.id << ", "
                << "name: " << territory.name << ", "
                << "continent: " << territory.continent->get_name() << ", "
                << "borders: " << territory.bordering_territories_tostring()
                << ")";
}

Territory& Territory::operator=(const Territory& c) {
    this->id = *(new int(c.id));
    this->name = *(new string(c.name));
    this->continent_id = *(new int(c.continent_id));
    this->bordering_territories = c.bordering_territories;

    return *this;
}


