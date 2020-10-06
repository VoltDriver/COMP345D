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

Country::Country(const Country &obj) {
    this->id = obj.get_id();
    this->name = obj.get_name();
    this->continent_id = obj.get_continent_id();
}


/* Accessors & Mutators */
string Country::get_name() const {
    return name;
}

int Country::get_id() const {
    return id;
}

int Country::get_continent_id() const {
    return continent_id;
}

void Country::set_continent(Continent *continent) {
    this->continent = continent;
}

Continent *Country::get_continent() const {
    return continent;
}

vector<Country *> Country::get_bordering_country() {
    return this->bordering_countries;
}


/* Methods */
void Country::add_bordering_country(Country *country) {
    bordering_countries.push_back(country);
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


/* Overloaders */
ostream &operator<<(std::ostream &strm, const Country &country) {
    return strm << "Country("
                << "id: " << country.id << ", "
                << "name: " << country.name << ", "
                << "continent: " << country.continent->get_name() << ", "
                << "borders: " << country.bordering_countries_tostring()
                << ")";
}






