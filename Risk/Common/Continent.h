#pragma once
#include <vector>
#include <string>

#include "Country.h"

using namespace std;

class Continent {
private:
    vector<Country*> territories;
    string name;
    int armies;
    string color;
public:
    Continent();
};