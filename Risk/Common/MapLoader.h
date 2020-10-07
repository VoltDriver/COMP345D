#pragma once

#include <string>
#include "Map.h"

class MapLoader {
private:
    Map* loaded_map = nullptr;

public:
    MapLoader();
    Map parse(string);
};


