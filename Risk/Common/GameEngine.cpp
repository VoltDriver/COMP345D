#include "GameEngine.h"
#include "MapLoader.h"
#include "Player.h"
#include "Cards.h"

#include <string>
#include <iostream>
#include <filesystem>
#include <vector>
#include <limits>

namespace fs = std::filesystem;
using namespace std;

/**
 * Displays available map names in Resource directory then prompts user for selection
 * @return Chosen map file name
 */
string map_select() {
    const string MAP_DIRECTORY = "../Resource/";
    vector<string> maps;

    cout << "============== MAP SELECT ==============" << endl;

    uint16_t index = 0;
    // Iterate, print and store each file in our map directory
    for (const auto &entry : fs::directory_iterator(MAP_DIRECTORY)) {
        maps.push_back(entry.path().filename().string());
        cout << "[" << ++index << "] - " << entry.path().filename() << endl;
    }
    cout << "========================================" << endl;

    int option;
    bool error = false;
    // Iterate until a valid input was received
    do {
        // Reset fail bit
        cin.clear();
        // Clear the cin buffer on invalid input (Causes infinite loops otherwise)
        error && cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << (error ? "Invalid input, try again! It's really not that complicated...\n" : "")
             << "Choose a map (Enter a corresponding number):";
        cin >> option;

        // Check for fail bit or OOB index
        error = !cin.good() || option < 1 || option > index;
    } while (error);

    cout << "\nYou selected map: " << maps.at(option) << endl;
    return maps.at(option);
}

/**
 * Prompts user for number of players. 2-5
 * @return chosen number of players
 */
int player_select() {
    const uint16_t MAX_PLAYERS = 5;
    const uint16_t MIN_PLAYERS = 2;

    cout << "============= PLAYER COUNT =============" << endl;
    int player_count;
    bool error = false;
    do {
        // Reset fail bit
        cin.clear();
        // Clear the cin buffer on invalid input (Causes infinite loops otherwise)
        error && cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << (error ? "Invalid input, try again! It's really not that complicated...\n" : "")
             << "Enter number of players (2-5):";
        cin >> player_count;

        // Check for fail bit or OOB index
        error = !cin.good() || player_count < MIN_PLAYERS || player_count > MAX_PLAYERS;
    } while (error);

    cout << "\nNumber of players: " << player_count << endl;

    return player_count;
}

/**
 * Prompts user to enable or disable implemented game observers
 * @return Pair containing user selection <phase_observer, stats_observer>
 */
pair<bool, bool> observer_settings() {
    char input;
    bool error = false, observer_phase = false, observer_stats = false;

    cout << "=========== OBSERVER SETTINGS ==========" << endl;

    do {
        // Reset fail bit
        cin.clear();
        // Clear the cin buffer on invalid input (Causes infinite loops otherwise)
        error && cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << (error ? "Invalid input, try again! It's really not that complicated...\n" : "")
             << "Enable the Phase observer? (y/n):";
        cin >> input;

        // Check for fail bit or OOB index
        error = !cin.good() || input != 'y' && input != 'n';
    } while (error);

    observer_phase = input == 'y';

    do {
        // Reset fail bit
        cin.clear();
        // Clear the cin buffer on invalid input (Causes infinite loops otherwise)
        error && cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << (error ? "Invalid input, try again! It's really not that complicated...\n" : "")
             << "Enable the Game Statistics observer? (y/n):";
        cin >> input;

        // Check for fail bit or OOB index
        error = !cin.good() || input != 'y' && input != 'n';
    } while (error);

    observer_stats = input == 'y';

    cout << "\nPhase Oberser has been " << (observer_phase ? "ENABLED" : "DISABLED");
    cout << "\nGame stats Observer has been " << (observer_stats ? "ENABLED" : "DISABLED") << endl;

    return make_pair(observer_phase, observer_stats);
}

void GameEngine::gameStart() {
    const string MAP_DIRECTORY = "../Resource/";

    // Display and choose map
    string map_filename = map_select();
    // Select number of players 2-5
    int num_of_players = player_select();
    // Turn off any observers
    pair<bool, bool> observer_options = observer_settings();

    this->phase_observer_flag = observer_options.first;
    this->stat_observer_flag = observer_options.second;

    // Load and set map
    try {
        this->map = MapLoader::parse(MAP_DIRECTORY + map_filename, false);
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }

    // Create and set players
    for (int i = 1; i <= num_of_players; i++) {
        this->players.push_back(new Player());
    }

    // Create and set the deck
    this->deck = new Deck();
}