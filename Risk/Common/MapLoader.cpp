#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "MapLoader.h"

using namespace std;

void MapLoader::parse(string fileName) {
    try {
        ifstream fileReader(fileName);

        string line;

        if (fileReader.fail()) {
            cout << "Error opening file" << endl;
        } else {

        }

        while (getline(fileReader, line)) {
            cout << line << endl;
        }

    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }
}