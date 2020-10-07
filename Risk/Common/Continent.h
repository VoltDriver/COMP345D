#pragma once

#include <vector>
#include <string>

using namespace std;

class Territory;

class Continent {
private:
    int armies = 0;
    string name;
    vector<Territory*> territories;
    friend ostream& operator<<(ostream&, const Continent&);

public:
    explicit Continent(string&);
    Continent(const Continent &obj);

    string get_name() const;
    vector<Territory*> get_territories() const;
    void add_territory(Territory* territory);

    Continent& operator=(const Continent &c);
};