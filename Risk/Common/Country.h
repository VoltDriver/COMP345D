#pragma once

#include <vector>
#include <string>
#include <ostream>

#include "Continent.h"

using namespace std;

class Country {
private:
    int id;
    string name;
    int continent_id;
    Continent* continent = nullptr;
    // Player* player = nullptr;
    vector<Country*> bordering_countries;
    friend ostream& operator<<(ostream&, const Country&);

public:
    explicit Country(string&);

    string get_name() const;
    int get_id() const;
    int get_continent_id() const;
    Continent* get_continent() const;
    void add_bordering_country(Country*);
    vector<Country*> get_bordering_country();
    string bordering_countries_tostring() const;
    bool borders_country(Country* country) const;
    void set_continent(Continent* continent);
};