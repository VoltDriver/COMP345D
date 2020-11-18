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

/**
 * Automated version of gameStart, to be used in Driver files not the main game!
 */
void GameEngine::gameStart_Auto(string map, int player_count, bool phase_observer, bool stat_observer) {
    this->phase_observer_flag = phase_observer;
    this->stat_observer_flag = stat_observer;

    // Creating observers
    if(this->phase_observer_flag) {
        phaseView = new PhaseObserver(this);
    }
    if(this->stat_observer_flag) {
        statsView = new StatsObserver(this);
    }

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

        Player* player = new Player(name);

        this->players.emplace_back(player);
    }
    // Create and set the deck
    this->deck = new Deck();

    cout << "\n\n=========== DEBUG OUTPUT ==========" << endl;
    cout << "Selected map: " << map << endl;
    cout << "Player count: " << player_count << endl;
    cout << "Phase observer: " << (phase_observer ? "Enabled" : "Disabled") << endl;
    cout << "Stats observer: " << (stat_observer ? "Enabled" : "Disabled") << endl;
    // Cards
    cout << "The Deck contains " << this->deck->remainingCards() << " cards." << endl;
    cout << "> Running map validation..." << endl;
    // Validate map
    auto temp_map = MapLoader::parse(MAP_DIRECTORY + map);
    delete temp_map;
    cout << "===================================" << endl;
}

/**
 * Sets the game rules using user input
 *
 * Lets the player choose the following options:
 * Player count
 * map
 * Enable/Disable Observers
 */
void GameEngine::gameStart(bool verbose) {
    // Display and choose map
    string map_filename = map_select();
    // Select number of players 2-5
    int num_of_players = player_select();
    // Turn on/off any observers
    pair<bool, bool> observer_options = observer_settings();
    // Set observer bools
    this->phase_observer_flag = observer_options.first;
    this->stat_observer_flag = observer_options.second;

    // Creating observers
    if(this->phase_observer_flag) {
        phaseView = new PhaseObserver(this);
    }
    if(this->stat_observer_flag) {
        statsView = new StatsObserver(this);
    }

    // Load and set map
    try {
        this->map = MapLoader::parse(MAP_DIRECTORY + map_filename, false);
    } catch (const std::exception &e) {
        verbose && (cout << "\n\n" << e.what() << endl);
        throw exception("Invalid map specified");
    }

    // Create and set players
    for (int i = 1; i <= num_of_players; i++) {
        string name = "Player " + std::to_string(i);

        Player* player = new Player(name);

        this->players.emplace_back(player);
    }

    // Create and set the deck
    this->deck = new Deck();

    if (verbose) {
        cout << "\n\n=========== DEBUG OUTPUT ==========" << endl;
        // Validate map
        cout << "> Running map validation..." << endl;
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
    // Phase Observer notification
    this->phase = "Startup Phase";
    Subject::notify();

    cout << "              " << endl;
    srand (time(NULL));
    list<Player*>::iterator it;
    vector<int> ordersOfPlay;

    // This switch statement takes different actions in terms of the values depending on the number of players in the game.

    switch(players.size()){
        case 2:
            cout << "40 initial armies for every player!" << endl;
            ordersOfPlay = {1,2};
            for(it = players.begin(); it != players.end(); ++it){
                (*it)->reinforcementPool = 40;
                (*it)->uncommittedReinforcementPool = 40;
                int random = rand() % ordersOfPlay.size();
                (*it)->orderOfPlay = ordersOfPlay[random];
                ordersOfPlay.erase(ordersOfPlay.begin() + random);
                ordersOfPlay.shrink_to_fit();
            }
            break;
        case 3:
            cout << "35 initial armies for every player!" << endl;
            ordersOfPlay = {1,2,3};
            for(it = players.begin(); it != players.end(); ++it){
                (*it)->reinforcementPool = 35;
                (*it)->uncommittedReinforcementPool = 35;
                int random = rand() % ordersOfPlay.size();
                (*it)->orderOfPlay = ordersOfPlay[random];
                ordersOfPlay.erase(ordersOfPlay.begin() + random);
                ordersOfPlay.shrink_to_fit();
            }
            break;
        case 4:
            cout << "30 initial armies for every player!" << endl;
            ordersOfPlay = {1,2,3,4};
            for(it = players.begin(); it != players.end(); ++it){
                (*it)->reinforcementPool = 30;
                (*it)->uncommittedReinforcementPool = 30;
                int random = rand() % ordersOfPlay.size();
                (*it)->orderOfPlay = ordersOfPlay[random];
                ordersOfPlay.erase(ordersOfPlay.begin() + random);
                ordersOfPlay.shrink_to_fit();
            }
            break;
        case 5:
            cout << "25 initial armies for every player!" << endl;
            ordersOfPlay = {1,2,3,4,5};
            for(it = players.begin(); it != players.end(); ++it){
                (*it)->reinforcementPool = 25;
                (*it)->uncommittedReinforcementPool = 25;
                int random = rand() % ordersOfPlay.size();
                (*it)->orderOfPlay = ordersOfPlay[random];
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
                Territory* territory = copyOfMapTerritories[random];
                territory->setPlayer(&*(*it));
                (*it)->territories.push_back(territory);
                copyOfMapTerritories.erase(copyOfMapTerritories.begin() + random);
                copyOfMapTerritories.shrink_to_fit();
            }
        }
    }

    // Showing the territories and reinforcement pool of each player.

    for(it = players.begin(); it != players.end(); ++it){
        cout << (*it)->name << ":" << endl;
        cout << "              " << endl;
        cout << "   Armies available in reinforcement pool: " << (*it)->reinforcementPool << endl;
        cout << "   Territories assigned: " << endl;
        for(int i = 0; i < (*it)->territories.size(); i++){
            cout<< "        " << (*it)->territories[i]->get_name() << endl;
        }
        cout << "------------------" << endl;
        cout << "              " << endl;
    }

    // Reordering the list of players, to implement order of play
    players.sort();
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
        // Phase Observer notification
        this->phase = "New Turn";
        this->turnCounter++;
        Subject::notify();

        // Reinforcement Phase
        reinforcementPhase();

        // Issuing Orders Phase
        issueOrdersPhase();

        // Orders Execution Phase
        executeOrdersPhase();

        // Checking if a player has lost
        auto it = players.begin();
        while (it != players.end()) {
            auto current = it++;
            if ((*current)->territories.empty()) {

                // Stats Observer notification
                this->phase = "Eliminated";
                this->currentPlayer = *current;
                Subject::notify();

                cout << (*current)->name << " has lost!" << endl;
                eliminatedPlayers.push_back(*current);
                players.erase(current);
            }
        }

        // Checking if the game is over
        for (Player* player : players) {
            if (player->territories.size() == map->get_territories().size()) {
                gameOver = true;
                winningPlayer = player->name;

                // Stats Observer notification
                this->phase = "Game Over";
                this->currentPlayer = player;
                Subject::notify();
            }
        }

    }

    cout << "The game is over! " << winningPlayer << " has won." << endl;
}

/**
 * Players are given armies according to the territories they own, including continent bonuses.
 */
void GameEngine::reinforcementPhase() {
    // Phase Observer notification
    this->phase = "Reinforcement Phase";
    Subject::notify();

    for (Player* player : players) {
        int reinforcement = 0;
        currentPlayer = player;
        currentPlayer->setUncommittedReinforcementPool(currentPlayer->reinforcementPool);

        int nbTerritoriesOwned = player->territories.size();

        // Int division because it is rounded down.
        reinforcement += nbTerritoriesOwned / 3;

        std::map<string, ContinentOwnership_DataObject> continentOwnership = std::map<string, ContinentOwnership_DataObject>();

        for (Territory *t : player->territories) {
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
        player->reinforcementPool += reinforcement;

        // Adjust the uncommitted reinforcement pool of the player
        player->uncommittedReinforcementPool += reinforcement;

        // Phase Observer notification
        this->phase = "Reinforcement Phase::Deploy";
        this->currentPlayer = player;
        Subject::notify();
    }
}

/**
 * Players issue orders, in a round robin fashion.
 */
void GameEngine::issueOrdersPhase() {
    // Phase Observer notification
    this->phase = "Issue Orders Phase";
    Subject::notify();

    // Contains whether a player is done with their turn or not. True if not done.
    std::map<string, bool> playerTurns = std::map<string, bool>();

    // Initializing the map
    for (Player* player : players) {
        playerTurns[player->name] = true;
    }


    // Creating a copy of the Players. We have to instantiate them manually, because we've
    // had weird problems with memory corruption otherwise.
    list<Player*> gamePlayers = list<Player*>();

    auto iterator = std::next(this->players.begin(), 0);

    for (int i = 0; i < players.size(); ++i) {
        Player* copyPlayer = (*iterator);
        gamePlayers.emplace_back(copyPlayer);
        iterator++;
    }


    // Going round robin until all turns are done.
    int amountOfPlayersDone = 0;

    while (amountOfPlayersDone != players.size()) {

        for (Player* player : players) {

            // If a player did not end his turn yet...
            if (playerTurns[player->name]) {

                // Phase Observer notification
                this->phase = "Issue Orders Phase::Player turn";
                this->currentPlayer = player;
                Subject::notify();

                // ... it is prompted to play.

                // Checking if we have human players.
                if(hasHumanPlayers)
                {
                    playerTurns[player->name] = player->issueOrderHuman(this->deck, this->map, gamePlayers);
                }
                else
                {
                    playerTurns[player->name] = player->issueOrder(this->deck, this->map, gamePlayers);
                }

                // If it decided to end it's turn just now...
                if (!playerTurns[player->name]) {

                    // Phase Observer notification
                    this->phase = "Issue Orders Phase::Turn end";
                    Subject::notify();

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
    // Phase Observer notification
    this->phase = "Execute Orders Phase";
    Subject::notify();

    // Contains whether a player is done with their orders or not. True if not done.
    std::map<string, bool> playerOrdersStatus = std::map<string, bool>();

    // Initializing the map
    for (Player* player : players) {
        playerOrdersStatus[player->name] = true;
    }

    // Going round robin until all orders are done.
    int amountOfPlayersDone = 0;

    while (amountOfPlayersDone != players.size()) {
        for (Player* player : players) {

            // If a player still is playing....
            if (playerOrdersStatus[player->name]) {
                // ... and still has orders...
                if (player->orders->myList.empty())
                {
                    // Phase Observer notification
                    this->phase = "Execute Orders Phase::Done";
                    this->currentPlayer = player;
                    Subject::notify();

                    // If it has no more orders... we add it to the number of players that are done.
                    playerOrdersStatus[player->name] = false;
                    amountOfPlayersDone++;
                }
                else
                {
                    // Phase Observer notification
                    this->phase = "Execute Orders Phase::Execute";
                    this->currentPlayer = player;
                    Subject::notify();

                    // ... it executes an order
                    player->orders->myList[0]->execute();

                    if (player->hasConquered()) {
                        // Stats Observer notification
                        this->phase = "Conquered";
                        Subject::notify();
                    }
                }
            }

            // if current player owns all territories (won the game), then leave the execute phase.
            if (player->to_defend().size() == map->get_territories().size()) {
                return;
            }

        }
    }

    // Every order has been executed.


    for(Player* p : players)
    {
        // Adding cards to players who conquered a territory.
        if(p->conquered)
        {
            deck->draw(p->hand);
            p->conquered = false;
        }

        // Resetting the Negotiate orders
        p->friendlyPlayers.clear();
    }
}

ostream &operator<<(ostream& out, const GameEngine& g) {
    string players;
    for(const Player* p : g.players)
    {
        players += p->name + " ";
    }
    return out << g.map << endl << g.deck << endl << players<< endl << g.stat_observer_flag << " " << g.phase_observer_flag;
}

GameEngine &GameEngine::operator=(const GameEngine &g) {
    if (this != &g) {
        delete this->currentPlayer;
        delete this->map;
        delete this->deck;

        for(Player* player : players)
        {
            delete player;
        }

        for(Player* player : eliminatedPlayers)
        {
            delete player;
        }

        currentPlayer = g.currentPlayer;
        phase = g.phase;
        turnCounter = g.turnCounter;
        players = g.players;
        map = g.map;
        deck = g.deck;
        phase_observer_flag = g.phase_observer_flag;
        stat_observer_flag = g.stat_observer_flag;
        eliminatedPlayers = g.eliminatedPlayers;
    }

    return *this;
}

GameEngine::GameEngine() {
    currentPlayer = new Player();
    phase = "";
    turnCounter = 0;
    players = list<Player*>();
    eliminatedPlayers = list<Player*>();
    map = new Map();
    deck = new Deck();
    phase_observer_flag = true;
    stat_observer_flag = true;
    hasHumanPlayers = false;
    phaseView = nullptr;
    statsView = nullptr;
}

GameEngine::GameEngine(const GameEngine &g) {
    currentPlayer = g.currentPlayer;
    phase = g.phase;
    turnCounter = g.turnCounter;
    players = g.players;
    eliminatedPlayers = g.eliminatedPlayers;
    map = g.map;
    deck = g.deck;
    phase_observer_flag = g.phase_observer_flag;
    stat_observer_flag = g.stat_observer_flag;
    hasHumanPlayers = g.hasHumanPlayers;
}

GameEngine::~GameEngine() {
    delete this->currentPlayer;
    delete this->phaseView;
    delete this->statsView;
    delete this->map;
    delete this->deck;

    for(Player* player : eliminatedPlayers)
    {
        delete player;
    }
}


Player* GameEngine::getCurrentPlayer() {
    return currentPlayer;
}

Map* GameEngine::getMap() {
    return map;
}

list<Player*> GameEngine::getPlayers(){
    return players;
}

string GameEngine::getPhase() {
    return phase;
}

int GameEngine::getTurnCounter() {
    return turnCounter;
}

void GameEngine::main() {
    gameStart(false);
    startupPhase();
    mainGameLoop();
}
