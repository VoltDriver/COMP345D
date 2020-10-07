#include <ostream>

#include "Continent.h"
#include "Util.h"


/* Constructors */
Continent::Continent(string &raw_continent) {
    const vector<string> continent_data = split(raw_continent);
    name = continent_data.at(0);
}

Continent::Continent(const Continent &c) {
    this->name = *(new string(c.name));
    this->territories = c.territories;
    this->armies = *(new int(c.armies));
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
ostream &operator<<(std::ostream& strm, const Continent &continent) {
    return strm << "Continent("
                << "name: " << continent.name
                << ")";
}

Continent& Continent::operator=(const Continent& c) {
    this->name = *(new string(c.name));
    this->territories = c.territories;
    this->armies = *(new int(c.armies));

    return *this;
}