#pragma once

#include <string>
#include "Map.h"

class MapLoader {
public:
    /* Constructors */
    MapLoader();

    /* Methods */
    virtual Map* parse(string file_name, bool verbose);
};

class ConquestFileReader {
public:
    Map* parse(string file_name, bool verbose = true);
};

class ConquestFileReaderAdapter : public MapLoader {
private:
    ConquestFileReader* _adaptee;
public:
    ConquestFileReaderAdapter(ConquestFileReader *adaptee) : _adaptee(adaptee) {};

    Map* parse(string file_name, bool verbose) override;
};


