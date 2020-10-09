#pragma once

#include <string>
#include "Map.h"

class MapLoader {
public:
    /* Constructors */
    MapLoader();

    /* Methods */
    static Map* parse(string);
};


