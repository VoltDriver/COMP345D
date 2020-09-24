#include <iostream>
#include <sstream>

#include "Util.h"

using namespace std;

vector<string> split(const string &str, char delimeter) {
    stringstream stream(str);
    string token;
    vector<string> tokens;

    while (getline(stream, token, delimeter)) {
        tokens.push_back(token);
    }

    return tokens;
}

vector<string> split(const string &str) {
    return split(str, ' ');
}