#include <ostream>

#include "Country.h"
#include "Util.h"

/* Constructors */
Country::Country(string &raw_country) {
    const vector<string> country_data = split(raw_country);

    this-> id = std::stoi(country_data.at(0));
    this-> name = country_data.at(1);
    this-> continent_name = country_data.at(2);
}

/* Accessors & Mutators */
string Country::get_name() {
    return this-> name;
}

/* Methods */
void Country::add_bordering_country(Country *country) {
    this-> bordering_countries.push_back(country);
}

/* Overloaders */
ostream &operator<<(std::ostream& strm, const Country &country) {
    return strm << "Country("
        << "id: " << country.id << ", "
        << "name: " << country.name
        << ")";
}