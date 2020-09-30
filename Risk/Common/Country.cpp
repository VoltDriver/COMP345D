#include <ostream>
#include <algorithm>

#include "Country.h"
#include "Util.h"

/* Constructors */
Country::Country(string &raw_country) {
    const vector<string> country_data = split(raw_country);

    this->id = std::stoi(country_data.at(0));
    this->name = country_data.at(1);
    this->continent_id = std::stoi(country_data.at(2));
}

/* Accessors & Mutators */
string Country::get_name() const {
    return this->name;
}

/* Methods */
void Country::add_bordering_country(Country *country) {
    bordering_countries.push_back(country);
}

/* Overloaders */
ostream &operator<<(std::ostream &strm, const Country &country) {
    return strm << "Country("
                << "id: " << country.id << ", "
                << "name: " << country.name << ", "
                << "continent: " << country.continent->get_name() << ", "
                << "borders: " << country.bordering_countries_tostring()
                << ")";
}

vector<Country *> Country::get_bordering_country() {
    return this->bordering_countries;
}

int Country::get_id() const {
    return id;
}

string Country::bordering_countries_tostring() const {
    string country_list = "(";
    for (Country *country: bordering_countries) {
        country_list += country->get_name();

        if (country != bordering_countries.back()) {
            country_list += ", ";
        }
    }

    country_list += ")";
    return country_list;
}

bool Country::borders_country(Country *comparator) const {
    return std::any_of(
            bordering_countries.begin(),
            bordering_countries.end(),
            [&](const Country *bordering_country) { return bordering_country == comparator; });
}

void Country::set_continent(Continent *continent) {
    this->continent = continent;
}

int Country::get_continent_id() const {
    return continent_id;
}

Continent *Country::get_continent() const {
    return continent;
}
