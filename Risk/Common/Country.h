#pragma once

#include <vector>
#include <string>
#include <ostream>

#include "Continent.h"

using namespace std;

class Country {
private:
    int id, continent_id;
    string name;
    Continent* continent = nullptr;
    // Player* player = nullptr;
    vector<Country*> bordering_countries;
    friend ostream& operator<<(ostream&, const Country&);

public:
    explicit Country(string&);
    Country(const Country &obj);

    string get_name() const;
    int get_id() const;
    int get_continent_id() const;
    void set_continent(Continent* continent);
    Continent* get_continent() const;
    vector<Country*> get_bordering_country();
    void add_bordering_country(Country*);
    string bordering_countries_tostring() const;
    bool borders_country(Country* country) const;
};