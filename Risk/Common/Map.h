#pragma once
#include <vector>
#include <string>

using namespace std;

class Player;
class Territory;

/**
 * Represents a continent on a map.
 * A continent has a bonus reinforcement amount indicated by the army bonus. Bonus will work when a player controls all
 * countries contained in a continent.
 * Each continent has a name.
 * All territories that belong to continent will be in the territories vector.
 */
class Continent {
private:
    int army_bonus = 0;
    string name;
    vector<Territory*> territories;

    friend ostream& operator<<(ostream&, const Continent&);

public:
    /* Constructors */
    explicit Continent(string&);
    Continent(const Continent &obj);

    /* Accessors & Mutators */
    string get_name() const;
    int get_army_bonus() const;
    vector<Territory*> get_territories() const;

    /* Methods */
    void add_territory(Territory* territory);

    /* Overloaders */
    Continent& operator=(const Continent &c);
};


/**
 * Represents a territory on a continent.
 * A territory is assigned an id which is how other territories and its continent will refer to it.
 * The continent id will indicate which continent on the map that it belongs to.
 * The armies represent the number of armies that are currently ona territory.
 * The name will provide the name of the territory.
 * Each territory will also have bordering countries which will be held in a vector of pointers that point
 * to the bordering territories.
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
    /* Constructors */
    Territory(int id, string name, int continent);
    explicit Territory(string&);
    Territory(const Territory &obj);

    /* Accessors & Mutators */
    int get_continent_id() const;
    int get_id() const;
    string get_name() const;
    vector<Territory*> get_bordering_territory();
    Continent* get_continent() const;
    void set_continent(Continent* continent);

    /* Methods */
    void add_bordering_territory(Territory *territory);
    bool borders_territory(Territory* bordering_territory) const;
    string bordering_territories_tostring() const;

    /* Overloaders */
    Territory& operator=(const Territory &c);
};


/**
 * Represents a map.
 * A map contains a vector of territory and continent objects.
 * It also has functions that help validate map files.
 */
class Map {
public:
    vector<Continent*> continents;
    vector<Territory*> territories;

    /* Constructors */
    Map();
    Map(const Map& map);

    /* Destructor  */
    ~Map();

    /* Accessors & Mutators */
    vector<Territory*> get_territories();
    vector<Continent*> get_continents();

    /* Methods */
    void add_territory(Territory* new_territory);
    void add_continent(Continent* new_continent);
    bool validate() const;
    bool verify_map_connected_graph() const;
    bool verify_continent_connected_subgraph() const;
    bool verify_unique_continents() const;

    /* Overloaders */
    Map& operator=(const Map& m);
};
