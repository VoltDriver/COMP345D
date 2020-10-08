#pragma once
#include <vector>
#include <string>

using namespace std;

class Player;
class Territory;

/**
 *
 */
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

/**
 *
 */
class Territory {
private:
    int id, continent_id, armies = 0;
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

/**
 *
 */
class Map {
private:
    vector<Continent*> continents;
    vector<Territory*> territories;

public:
    ~Map();

    vector<Territory*> get_territories();
    vector<Continent*> get_continents();
    void add_territory(Territory* new_territory);
    void add_continent(Continent* new_continent);
    bool validate() const;
    bool verify_map_connected_graph() const;
    bool verify_continent_connected_subgraph() const;
    bool verify_unique_continents() const;
};
