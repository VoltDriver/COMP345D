#pragma once

#include <vector>
#include <string>

using namespace std;

class Country;

class Continent {
private:
    vector<Country*> countries;
    string name;
    int armies = 0;
    friend ostream& operator<<(ostream&, const Continent&);

public:
    explicit Continent(string&);
    string get_name() const;
    void add_country(Country* country);
    vector<Country*> get_countries() const;
};