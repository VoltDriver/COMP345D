#pragma once

#include <vector>
#include <string>

using namespace std;

class Country;

class Continent {
private:
    int armies = 0;
    string name;
    vector<Country*> countries;
    friend ostream& operator<<(ostream&, const Continent&);

public:
    explicit Continent(string&);
    Continent(const Continent &obj);

    string get_name() const;
    vector<Country*> get_countries() const;
    void add_country(Country* country);
};