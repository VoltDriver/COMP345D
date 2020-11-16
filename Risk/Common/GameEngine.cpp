#include "GameEngine.h"
#include "MapLoader.h"
#include "Player.h"
#include "Cards.h"

#include <string>
#include <iostream>
#include <cstdlib>
#include <filesystem>
#include <vector>
#include <limits>


namespace fs = std::filesystem;
using namespace std;

/// Constitutes the minimum amount of reinforcement per turn per player.
const int GameEngine::MINIMUM_REINFORCEMENT = 3;
const char * GameEngine::MAP_DIRECTORY = "../Resource/";

/**
 * Displays available map names in Resource directory then prompts user for selection
 * @return Chosen map file name
 */
string GameEngine::map_select() {
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

    cout << "\nYou selected map: " << maps.at(option - 1) << endl;
    return maps.at(option - 1);
}

/**
 * Prompts user for number of players. 2-5
 * @return chosen number of players
 */
int GameEngine::player_select() {
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
pair<bool, bool> GameEngine::observer_settings() {
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

    cout << "\nPhase Observer has been " << (observer_phase ? "ENABLED" : "DISABLED");
    cout << "\nGame stats Observer has been " << (observer_stats ? "ENABLED" : "DISABLED") << endl;

    return make_pair(observer_phase, observer_stats);
}

void GameEngine::gameStart_Auto(string map, int player_count, bool phase_observer, bool stat_observer) {
    this->phase_observer_flag = phase_observer;
    this->stat_observer_flag = stat_observer;

    // Load and set map
    try {
        this->map = MapLoader::parse(MAP_DIRECTORY + map, false);
    } catch (const std::exception &e) {
        cout << e.what() << endl;

        throw exception("Invalid map specified");
    }

    // Create and set players
    for (int i = 1; i <= player_count; i++) {
        string name = "Player " + std::to_string(i);
        this->players.emplace_back(name);
    }
    // Create and set the deck
    this->deck = new Deck();

    cout << "\n\n=========== DEBUG OUTPUT ==========" << endl;
    cout << "Selected map: " << map << endl;
    cout << "Player count: " << player_count << endl;
    cout << "Phase obserber: " << (phase_observer ? "Enabled" : "Disabled") << endl;
    cout << "Stat obserber: " << (stat_observer ? "Enabled" : "Disabled") << endl;

    cout << "> Running map validation..." << endl;
    // Validate map
    //this->map->validate();
    auto temp_map = MapLoader::parse(MAP_DIRECTORY + map);
    delete temp_map;

    // Cards
    cout << "The Deck contains " << this->deck->remainingCards() << " cards." << endl;
    cout << "===================================" << endl;
}

void GameEngine::gameStart(bool verbose) {

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

        throw exception("Invalid map specified");
    }

    // Create and set players
    for (int i = 1; i <= num_of_players; i++) {
        string name = "Player " + std::to_string(i);
        this->players.emplace_back(name);
    }

    // Create and set the deck
    this->deck = new Deck();

    if (verbose) {
        cout << "\n\n=========== DEBUG OUTPUT ==========" << endl;
        // Validate map
        cout << "> Running map validation..." << endl;
        //this->map->validate();
        auto temp_map = MapLoader::parse(MAP_DIRECTORY  + map_filename);
        delete temp_map;

        // Right number of players/Cards
        cout << "There are " << this->players.size() << " player objects." << endl;
        cout << "The Deck contains " << this->deck->remainingCards() << " cards." << endl;
        cout << "===================================" << endl;
    }
}

/**
 * Giving each player a random order of play and armies in reinforcement pool. Assigning territories in a round robin fashion.
 */
void GameEngine::startupPhase(){
    phase = "Startup Phase";
    notify();
    cout << "              " << endl;
    srand (time(NULL));
    list<Player>::iterator it;
    vector<int> ordersOfPlay;

    // This switch statement takes different actions in terms of the values depending on the number of players in the game.

    switch(players.size()){
        case 2:
            cout << "40 initial armies for every player!" << endl;
            ordersOfPlay = {1,2};
            for(it = players.begin(); it != players.end(); ++it){
                it->reinforcementPool = 40;
                int random = rand() % ordersOfPlay.size();
                it->orderOfPlay = ordersOfPlay[random];
                ordersOfPlay.erase(ordersOfPlay.begin() + random);
                ordersOfPlay.shrink_to_fit();
            }
            break;
        case 3:
            cout << "35 initial armies for every player!" << endl;
            ordersOfPlay = {1,2,3};
            for(it = players.begin(); it != players.end(); ++it){
                it->reinforcementPool = 35;
                int random = rand() % ordersOfPlay.size();
                it->orderOfPlay = ordersOfPlay[random];
                ordersOfPlay.erase(ordersOfPlay.begin() + random);
                ordersOfPlay.shrink_to_fit();
            }
            break;
        case 4:
            cout << "30 initial armies for every player!" << endl;
            ordersOfPlay = {1,2,3,4};
            for(it = players.begin(); it != players.end(); ++it){
                it->reinforcementPool = 30;
                int random = rand() % ordersOfPlay.size();
                it->orderOfPlay = ordersOfPlay[random];
                ordersOfPlay.erase(ordersOfPlay.begin() + random);
                ordersOfPlay.shrink_to_fit();
            }
            break;
        case 5:
            cout << "25 initial armies for every player!" << endl;
            ordersOfPlay = {1,2,3,4,5};
            for(it = players.begin(); it != players.end(); ++it){
                it->reinforcementPool = 25;
                int random = rand() % ordersOfPlay.size();
                it->orderOfPlay = ordersOfPlay[random];
                ordersOfPlay.erase(ordersOfPlay.begin() + random);
                ordersOfPlay.shrink_to_fit();
            }
            break;
    }

    cout << "------------------------------" << endl;

    // creating a copy of map territories pointers.

    vector<Territory*> copyOfMapTerritories(map->territories.size());
    for(int i = 0; i < map->territories.size(); i++){
        copyOfMapTerritories[i] = map->territories[i];
    }

    // Giving each player territories in a round robin fashion.

    while(copyOfMapTerritories.size() != 0){
        for(it = players.begin(); it != players.end(); ++it){
            if(copyOfMapTerritories.size() != 0) {
                int random = rand() % copyOfMapTerritories.size();
                it->territories.push_back(copyOfMapTerritories[random]);
                copyOfMapTerritories.erase(copyOfMapTerritories.begin() + random);
                copyOfMapTerritories.shrink_to_fit();
            }
        }
    }

    // Showing the territories and reinforcement pool of each player.

    for(it = players.begin(); it != players.end(); ++it){
        cout << it->name << ":" << endl;
        cout << "              " << endl;
        cout << "   Armies available in reinforcement pool: " << it->reinforcementPool << endl;
        cout << "   Territories assigned: " << endl;
        for(int i = 0; i < it->territories.size(); i++){
            cout<< "        " << it->territories[i]->get_name() << endl;
        }
        cout << "------------------" << endl;
        cout << "              " << endl;
    }
}



// Continent_ArmyBonus_OwnedTerritories_DataObject

ContinentOwnership_DataObject::ContinentOwnership_DataObject() {
    continent = nullptr;
    armyBonus = 0;
    ownedTerritories = 0;
}

ContinentOwnership_DataObject::ContinentOwnership_DataObject(Continent *c, int ab, int ot) {
    continent = c;
    armyBonus = ab;
    ownedTerritories = ot;
}

ostream &operator<<(ostream& out, const ContinentOwnership_DataObject& c) {
    return out << c.continent->get_name() << " " << c.armyBonus << " " << c.ownedTerritories;
}

ContinentOwnership_DataObject::ContinentOwnership_DataObject(const ContinentOwnership_DataObject &c) {
    continent = c.continent;
    armyBonus = c.armyBonus;
    ownedTerritories = c.ownedTerritories;
}

ContinentOwnership_DataObject &ContinentOwnership_DataObject::operator=(const ContinentOwnership_DataObject &c) {
    delete this->continent;

    continent = c.continent;
    armyBonus = c.armyBonus;
    ownedTerritories = c.ownedTerritories;

    return *this;
}

/**
 * Runs the Warzone game, in a loop, until a player wins.
 * It calls, in order, the Reinforcement Phase, the Issue Orders Phase, and the Execute Orders Phase.
 */
void GameEngine::mainGameLoop() {
    bool gameOver = false;
    string winningPlayer;

    while (!gameOver) {
        // Reinforcement Phase
        reinforcementPhase();

        // Issuing Orders Phase
        issueOrdersPhase();

        // Orders Execution Phase
        executeOrdersPhase();

        // Checking if the game is over
        for (const Player& player : players) {
            if (player.territories.size() == map->get_territories().size()) {
                gameOver = true;
                winningPlayer = player.name;
            }
        }

        // Checking if a player has lost
        auto it = players.begin();
        while (it != players.end()) {
            auto current = it++;
            if (current->territories.empty()) {
                cout << current->name << " has lost!";
                players.erase(current);
            }
        }
    }

    cout << "The game is over! " << winningPlayer << " has won.";
    delete currentPlayer;
}

/**
 * Players are given armies according to the territories they own, including continent bonuses.
 */
void GameEngine::reinforcementPhase() {
    this->phase = "Reinforcement Phase";

    for (Player &player : players) {
        this->currentPlayer = &player;

        int reinforcement = 0;

        int nbTerritoriesOwned = player.territories.size();

        // Int division because it is rounded down.
        reinforcement += nbTerritoriesOwned / 3;

        std::map<string, ContinentOwnership_DataObject> continentOwnership = std::map<string, ContinentOwnership_DataObject>();

        for (Territory *t : player.territories) {
            // Checking if the continent is already part of the map
            if (continentOwnership.find(t->get_continent()->get_name()) == continentOwnership.end()) {
                // ... if it's not there, then we add it in.
                continentOwnership[t->get_continent()->get_name()] = ContinentOwnership_DataObject(
                        t->get_continent(),
                        t->get_continent()->get_army_bonus(),
                        0);
            }

            // Adding 1 to the amount of territories owned of that continent.
            continentOwnership[t->get_continent()->get_name()].ownedTerritories += 1;
        }

        // Now calculating the Army Bonus for whole continent ownership
        for (auto &entry : continentOwnership) {
            if (entry.second.continent->get_territories().size() == entry.second.ownedTerritories) {
                reinforcement += entry.second.armyBonus;
            }
        }

        // Ensuring the minimum reinforcement rule is applied
        if (reinforcement < MINIMUM_REINFORCEMENT) {
            reinforcement = MINIMUM_REINFORCEMENT;
        }

        // Place the reinforcements in the players' pools.
        player.reinforcementPool += reinforcement;
        Subject::notify();   // Reinforcement Phase
    }
}

/**
 * Players issue orders, in a round robin fashion.
 */
void GameEngine::issueOrdersPhase() {
    this->phase = "Issue Orders Phase";

    // Contains whether a player is done with their turn or not. True if not done.
    std::map<string, bool> playerTurns = std::map<string, bool>();

    // Initializing the map
    for (Player &player : players) {
        playerTurns[player.name] = true;
    }

    // Going round robin until all turns are done.
    int amountOfPlayersDone = 0;

    while (amountOfPlayersDone != players.size()) {
        for (Player &player : players) {
            // If a player did not end his turn yet...
            if (playerTurns[player.name]) {
                // ... it is prompted to play.
                playerTurns[player.name] = player.issueOrder(this->deck, this->map);

                // If it decided to end it's turn just now...
                if (!playerTurns[player.name]) {
                    // ... we add it to the number of players that are done.
                    amountOfPlayersDone++;
                }
            }
        }
    }

    // Everyone has played.
}

/**
 * Executes orders in the players' lists of orders in a round robin fashion.
 */
void GameEngine::executeOrdersPhase() {
    this->phase = "Execute Orders Phase";

    // Contains whether a player is done with their orders or not. True if not done.
    std::map<string, bool> playerOrdersStatus = std::map<string, bool>();

    // Initializing the map
    for (Player &player : players) {
        playerOrdersStatus[player.name] = true;
    }

    // Going round robin until all orders are done.
    int amountOfPlayersDone = 0;

    while (amountOfPlayersDone != players.size()) {
        for (Player &player : players) {
            // If a player still is playing....
            if (playerOrdersStatus[player.name]) {
                // ... and still has orders...
                if (player.orders.empty())
                {
                    // If it has no more orders... we add it to the number of players that are done.
                    playerOrdersStatus[player.name] = false;
                    amountOfPlayersDone++;
                }
                else
                {
                    // ... it executes an order
                    /* TODO: replace with ordersList. Also, check that once an order is executed, it is removed from the
                    list of a player's orders. */
                    player.orders[0]->execute();
                }
            }
        }
    }

    // Every order has been executed.
}

ostream &operator<<(ostream& out, const GameEngine& g) {
    string players;
    for(const Player& p : g.players)
    {
        players += p.name + " ";
    }
    return out << g.map << endl << g.deck << endl << players<< endl << g.stat_observer_flag << " " << g.phase_observer_flag;
}

GameEngine &GameEngine::operator=(const GameEngine &g) {
    if (this != &g) {
        delete this->currentPlayer;
        delete this->map;
        delete this->deck;

        currentPlayer = g.currentPlayer;
        players = g.players;
        map = g.map;
        deck = g.deck;
        phase_observer_flag = g.phase_observer_flag;
        stat_observer_flag = g.stat_observer_flag;
    }

    return *this;
}

GameEngine::GameEngine() {
    currentPlayer = new Player();
    players = list<Player>();
    map = new Map();
    deck = new Deck();
    phase_observer_flag = true;
    stat_observer_flag = true;
}

GameEngine::GameEngine(const GameEngine &g) {
    currentPlayer = g.currentPlayer;
    players = g.players;
    map = g.map;
    deck = g.deck;
    phase_observer_flag = g.phase_observer_flag;
    stat_observer_flag = g.stat_observer_flag;
}

GameEngine::~GameEngine() {
    delete this->currentPlayer;
    delete this->map;
    delete this->deck;
}


bool GameEngine::getPhase_observer_flag() {
    return phase_observer_flag;
}

bool GameEngine::getStat_observer_flag(){
    return stat_observer_flag;
}

Player* GameEngine::getCurrentPlayer() {
    return currentPlayer;
}

string GameEngine::getPhase() {
    return phase;
}

