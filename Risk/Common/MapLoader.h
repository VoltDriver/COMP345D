#pragma once

#include <string>
#include "Map.h"

class MapLoader {
public:
    MapLoader();
    static Map* parse(string);
};


