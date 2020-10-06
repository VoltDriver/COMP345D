#include <iostream>

#include "Common/Map.h"
#include "Common/MapLoader.h"

int main() {
    MapLoader loader = MapLoader();
    try {
        loader.parse("../Resource/test5_duplicate_country.map");
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }

    return 0;
}
