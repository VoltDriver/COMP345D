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
    string continent_name;
    vector<Country*> bordering_countries;

    friend ostream& operator<<(ostream&, const Country&);

public:
    explicit Country(string&);

    string get_name();
    void add_bordering_country(Country*);
};