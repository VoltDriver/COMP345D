#pragma once

#include <vector>
#include <string>
#include <ostream>

#include "Continent.h"

using namespace std;

class Player;

class Territory {
private:
    int id, continent_id, armies;
    string name;
    Continent* continent = nullptr;
    Player* player = nullptr;
    vector<Territory*> bordering_territories;
    friend ostream& operator<<(ostream&, const Territory&);

public:
    Territory(int id, string name, int continent);
    explicit Territory(string&);
    Territory(const Territory &obj);

    string get_name() const;
    int get_id() const;
    int get_continent_id() const;
    void set_continent(Continent* continent);
    Continent* get_continent() const;
    vector<Territory*> get_bordering_territory();
    void add_bordering_territory(Territory *territory);
    string bordering_territories_tostring() const;
    bool borders_territory(Territory* bordering_territory) const;

    Territory& operator=(const Territory &c);
};