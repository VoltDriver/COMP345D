#include <ostream>

#include "Continent.h"
#include "Util.h"

/* Constructors */
Continent::Continent(string &raw_continent) {
    const vector<string> continent_data = split(raw_continent);
    this-> name = continent_data.at(0);
}

/* Overloaders */
ostream &operator<<(std::ostream& strm, const Continent &continent) {
    return strm << "Continent("
                << "name: " << continent.name
                << ")";
}