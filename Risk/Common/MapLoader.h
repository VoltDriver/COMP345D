#pragma once

#include <string>
#include "Map.h"

class MapLoader {
private:
    Map* current;
public:
    static void parse(string fileName);
};


