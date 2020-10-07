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
    this->countries = c.countries;
    this->armies = *(new int(c.armies));
}


/* Accessors & Mutators */
string Continent::get_name() const {
    return name;
}

vector<Country *> Continent::get_countries() const {
    return countries;
}


/* Methods */
void Continent::add_country(Country *country) {
    countries.push_back(country);
}


/* Overloaders */
ostream &operator<<(std::ostream& strm, const Continent &continent) {
    return strm << "Continent("
                << "name: " << continent.name
                << ")";
}

Continent& Continent::operator=(const Continent& c) {
    this->name = *(new string(c.name));
    this->countries = c.countries;
    this->armies = *(new int(c.armies));

    return *this;
}