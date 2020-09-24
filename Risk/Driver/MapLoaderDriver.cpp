#include <iostream>

#include "Common/Map.h"
#include "Common/MapLoader.h"

int main() {
    Map::validate();
    MapLoader loader = MapLoader();
    loader.parse("../Resource/test.map");

    return 0;
}
