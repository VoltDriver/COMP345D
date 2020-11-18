#include <iostream>
#include <map>
#include <set>
#include <random>
#include "Player.h"
#include "Cards.h"
#include "Orders.h"

// Number of Possible actions the user can take
const int NUMBER_OF_POSSIBLE_ACTIONS = 4;

// default constructor
Player::Player() {
    this->territories = vector<Territory*>();
    this->orders = new OrdersList();
    this->hand = new Hand();
    this->name = "";
    this->reinforcementPool = 0;
    this->uncommittedReinforcementPool = 0;
    this->conquered = false;
    this->orderOfPlay = 0;
    this->friendlyPlayers = vector<Player*>();
}

// parameterized constructors
Player::Player(string name) {
    this->territories = vector<Territory*>();
    this->orders = new OrdersList();
    this->hand = new Hand();
    this->name = name;
    this->reinforcementPool = 0;
    this->uncommittedReinforcementPool = 0;
    this->conquered = false;
    this->orderOfPlay = 0;
    this->friendlyPlayers = vector<Player*>();
}


Player::Player(vector<Territory*> territories, OrdersList* orders, Hand* hand, int orderOfPlay) {
    this->territories = territories;
    for (int i = 0; i < territories.size(); i++){
        territories.at(i)->setPlayer(this);
    }
    this->orders = orders;
    this->hand = hand;
    this->name = "";
    this->reinforcementPool = 0;
    this->uncommittedReinforcementPool = 0;
    this->conquered = false;
    this->orderOfPlay = orderOfPlay;
    this->friendlyPlayers = vector<Player*>();
}

Player::Player(vector<Territory*> territories, OrdersList* orders, Hand* hand, string name, int orderOfPlay) {
    this->territories = territories;
    this->orders = orders;
    this->hand = hand;
    this->name = name;
    this->reinforcementPool = 0;
    this->uncommittedReinforcementPool = 0;
    this->conquered = false;
    this->orderOfPlay = orderOfPlay;
    this->friendlyPlayers = vector<Player*>();
}

// copy constructor
Player::Player(const Player &p) {
    this->territories = p.territories;
    this->orders = p.orders;
    this->hand = p.hand;
    this->name = p.name;
    this->reinforcementPool = p.reinforcementPool;
    this->uncommittedReinforcementPool = p.uncommittedReinforcementPool;
    this->conquered = p.conquered;
    this->orderOfPlay = p.orderOfPlay;
    this->friendlyPlayers = p.friendlyPlayers;
}


/* Destructor */
Player::~Player() {
    for (Territory *territory: territories) {
        delete territory;
    }
    delete orders;
    for (Player* player: friendlyPlayers){
        delete player;
    }
    delete hand;
}


/* Methods */
void Player::addOrder(Order* order) {
    orders->add(order);
    cout << "order has been added to list of orders" << endl;
}

void Player::addTerritory(Territory *territory) {
    territories.push_back(territory);
    territory->setPlayer(this);
}

void Player::removeTerritory(Territory *territory) {
    for (int i = 0; i < territories.size() ; i++){
        if (territories.at(i)->get_id() == territory->get_id()) {
            territories.erase(territories.begin() + i);
            territories.shrink_to_fit();
        }
    }
}

int Player::getReinforcementPool() const {
    return reinforcementPool;
}

void Player::setReinforcementPool(int newPool) {
    this->reinforcementPool = newPool;
}

int Player::getUncommittedReinforcementPool() const {
    return uncommittedReinforcementPool;
}
void Player::setUncommittedReinforcementPool(int newPool) {
    this->uncommittedReinforcementPool = newPool;
}


/// Prompts the player to issue an order. Returns True if an order was issued, false otherwise.

/**
 * Makes a player issue an order. This is meant to be used by an AI player.
 * @return True if an order was issued, false otherwise.
 */
bool Player::issueOrder(Deck *deck, Map* territoriesMap, const list<Player*> gamePlayers) {
    int actionNumber = -1;

    // We use Mt19937 and random_device, which seeds the random generator with some random data from the system.
    // There's other ways to do it, but this is efficient and does not require seeding with Time.
    std::random_device randomDevice;
    std::mt19937 mt(randomDevice());

    // ID Generator
    ID generator = ID();

    // If some reinforcements are left in the pool of the player, he can only take deploy actions.
    if(this->uncommittedReinforcementPool > 0)
    {
        cout << "You have reinforcements in your pool. Only deploy orders are allowed." << endl;
        // Deploy
        actionNumber = 0;
    }
    else
    {
        list<int> possibleActions = list<int>();

        // Advance
        bool advanceAllowed = false;
        // Checking if an advance can be done
        for(Territory* t : territories)
        {
            if(t->get_armies() > 0)
                advanceAllowed = true;
        }

        if(advanceAllowed)
            possibleActions.push_back(1);

        // Play a card
        if(this->hand->remainingCards() > 0)
            possibleActions.push_back(2);

        // End turn
        possibleActions.push_back(3);

        // Generate a random input
        std::uniform_int_distribution<int> distribution(0, possibleActions.size() - 1);

        auto iterator = std::next(possibleActions.begin(), distribution(mt));
        actionNumber = *iterator ;
    }

    // Depending on which action was chosen, create an appropriate order.
    switch(actionNumber)
    {
        case 0:
        {
            // Deploy

            // Choose a territory
            std::map<int, Territory*> territoryToNumberMap = map<int, Territory*>();
            int counter = 0;
            for(Territory* t : to_defend())
            {
                territoryToNumberMap[counter] = t;
                counter++;
            }

            // Generate a random input
            std::uniform_int_distribution<int> distribution(0,territoryToNumberMap.size() - 1);

            int territoryChoice = distribution(mt);

            // Generate a random input
            std::uniform_int_distribution<int> distributionTroops(1,this->uncommittedReinforcementPool);
            int troopNumber = distributionTroops(mt);

            auto* deployOrder = new Deploy(generator.setID(), troopNumber, territoryToNumberMap[territoryChoice], this);
            addOrder(deployOrder);

            cout << "Deploy order issued." << endl;

            // Adjust the uncommitted reinforcement pool.
            this->uncommittedReinforcementPool -= troopNumber;
            break;
        }
        case 1:
        {
            // Advance

            // Choosing a starting point
            std::map<int, Territory*> sourceTerritoryToNumberMap = map<int, Territory*>();
            int counter = 0;

            for(Territory* t : this->to_defend())
            {
                // We can choose a starting point only if it has any armies.
                if(t->get_armies() > 0)
                {
                    sourceTerritoryToNumberMap[counter] = t;
                    counter++;
                }
            }

            // Generate a random input
            std::uniform_int_distribution<int> distribution(0,sourceTerritoryToNumberMap.size() - 1);

            int sourceTerritoryChoice = distribution(mt);

            // Choosing randomly a number of troops to move
            std::uniform_int_distribution<int> distributionTroops(1,sourceTerritoryToNumberMap[sourceTerritoryChoice]->get_armies());

            int troopNumber = distributionTroops(mt);

            // Choose a territory for the player to advance to.
            std::map<int, Territory*> destinationTerritoryToNumberMap = map<int, Territory*>();
            int counter2 = 0;

            // Advancing to attack
            for(Territory* t : this->to_attack())
            {
                if(sourceTerritoryToNumberMap[sourceTerritoryChoice]->borders_territory(t))
                {
                    destinationTerritoryToNumberMap[counter2] = t;
                    counter2++;
                }
            }
            // Advancing to defend
            for(Territory* t : this->to_defend())
            {
                if(sourceTerritoryToNumberMap[sourceTerritoryChoice]->borders_territory(t))
                {
                    destinationTerritoryToNumberMap[counter2] = t;
                    counter2++;
                }
            }

            // Choosing randomly a territory to move to
            std::uniform_int_distribution<int> distributionDestination(0,destinationTerritoryToNumberMap.size() - 1);

            int destinationTerritoryChoice = distributionDestination(mt);

            Advance* advanceOrder = new Advance(generator.setID(), troopNumber, sourceTerritoryToNumberMap.at(sourceTerritoryChoice), destinationTerritoryToNumberMap.at(destinationTerritoryChoice), this);
            addOrder(advanceOrder);

            cout << "Advance order issued." << endl;
            break;
        }
        case 2:
        {
            // Play a card

            int counter = 0;
            std::map<int, Card*> cardsToNumbers = std::map<int, Card*>();

            // Creating an iterator
            std::list<Card>::iterator iterator;
            // Iterating through the hand
            for (iterator = hand->cards->begin(); iterator != hand->cards->end(); ++iterator) {
                cardsToNumbers[counter] = &*iterator;
                counter++;
            }

            // Generate a random input
            std::uniform_int_distribution<int> distribution(0,hand->remainingCards() - 1);
            int cardChoice = distribution(mt);

            // Playing the card.
            Card* card = cardsToNumbers[cardChoice];

            cout << "Playing a card: " + card->toString() << endl;
            card->play(this, deck, territoriesMap, gamePlayers);
            break;
        }
        case 3:
            // End Turn
            cout << "Ending turn.\n" << endl;
            return false;
        default:
            throw exception("Invalid action chosen for a player's turn.");
    }

    return true;
}


/**
 * Prompts the player to issue an order. This is meant to be used by a human player.
 * @return True if an order was issued, false otherwise.
 */
bool Player::issueOrderHuman(Deck* deck, Map* territoriesMap, const list<Player*> gamePlayers) {
    int actionNumber = -1;

    cout << this->name << ", which order would you like to issue? (input the number)" << endl;
    cout << "List of possible orders:" << endl;

    // ID Generator
    ID generator = ID();

    // If some reinforcements are left in the pool of the player, he can only take deploy actions.
    if(this->uncommittedReinforcementPool > 0)
    {
        // Deploy
        cout << "0: Deploy " << endl;
        cout << "(You have " << this->uncommittedReinforcementPool << " reinforcements left in your pool. You must deploy them before issuing any other order." << endl;

        // Validate input.
        while(actionNumber != 0)
            cin >> actionNumber;
    }
    else
    {
        list<int> possibleActions = list<int>();

        // Advance
        bool advanceAllowed = false;
        // Checking if an advance can be done
        for(Territory* t : territories)
        {
            if(t->get_armies() > 0)
                advanceAllowed = true;
        }

        if(advanceAllowed) {
            possibleActions.push_back(1);
            cout << "1: Advance " << endl;
        }

        // Play a card
        if(this->hand->remainingCards() > 0)
        {
            possibleActions.push_back(2);
            cout << "2: Play a card" << endl;
        }

        // End turn
        possibleActions.push_back(3);
        cout << "3: End your turn." << endl;

        // Validate input.
        while(actionNumber<0 ||
        actionNumber >= NUMBER_OF_POSSIBLE_ACTIONS ||
        (std::find(possibleActions.begin(), possibleActions.end(), actionNumber) == possibleActions.end()))
            cin >> actionNumber;
    }

    // Depending on which action was chosen, create an appropriate order.
    switch(actionNumber)
    {
        case 0:
        {
            // Deploy

            // List the territories the player can choose
            cout << "In which territory would you like to deploy your troops?"<< endl;
            std::map<int, Territory*> territoryToNumberMap = map<int, Territory*>();
            int counter = 0;
            for(Territory* t : to_defend())
            {
                territoryToNumberMap[counter] = t;

                cout << counter << ": " << t->get_name() << " (" << t->get_armies() << " troops)" << endl;
                counter++;
            }

            // Read input and validate it.
            int territoryChoice = -1;
            while(territoryChoice<0 || territoryChoice > to_defend().size())
                cin >> territoryChoice;

            cout << "How many troops would you like to deploy? (" << this->uncommittedReinforcementPool << " remaining in your reinforcement pool.)" << endl;

            // Read input and validate it.
            int troopNumber = -1;
            while(troopNumber<0 || troopNumber > this->uncommittedReinforcementPool)
                cin >> troopNumber;

            auto* deployOrder = new Deploy(generator.setID(), troopNumber, territoryToNumberMap[territoryChoice], this);
            addOrder(deployOrder);

            cout << "Deploy order issued." << endl;

            // Adjust the uncommitted reinforcement pool
            this->uncommittedReinforcementPool -= troopNumber;
            break;
        }
        case 1:
        {
            // Advance

            // List the territories the player can choose as starting point
            cout << "From which territory would you like to select troops from?"<< endl;
            std::map<int, Territory*> sourceTerritoryToNumberMap = map<int, Territory*>();
            int counter = 0;
            for(Territory* t : to_defend())
            {
                // We can choose a starting point only if there are armies in it.
                if(t->get_armies() > 0)
                {
                    sourceTerritoryToNumberMap[counter] = t;

                    cout << counter << ": " << t->get_name() << " (" << t->get_armies() << " troops)" << endl;
                    counter++;
                }
            }

            // Read input and validate it.
            int sourceTerritoryChoice = -1;
            while(sourceTerritoryChoice<0 || sourceTerritoryChoice > to_defend().size())
                cin >> sourceTerritoryChoice;

            cout << "How many troops would you like to move? (" << sourceTerritoryToNumberMap[sourceTerritoryChoice]->get_armies() << " remaining in your territory.)" << endl;

            // Read input and validate it.
            int troopNumber = -1;
            while(troopNumber<0 || troopNumber > sourceTerritoryToNumberMap[sourceTerritoryChoice]->get_armies())
                cin >> troopNumber;

            // List the territories the player can choose to advance to
            cout << "To which territory would you like to advance your troops to?"<< endl;
            std::map<int, Territory*> destinationTerritoryToNumberMap = map<int, Territory*>();
            int counter2 = 0;

            cout << "Territories to attack: " << endl;
            for(Territory* t : this->to_attack())
            {
                if(sourceTerritoryToNumberMap[sourceTerritoryChoice]->borders_territory(t))
                {
                    destinationTerritoryToNumberMap[counter2] = t;
                    cout << counter2 << ": " << t->get_name() << " (" << t->get_armies() << " troops)" << endl;
                    counter2++;
                }
            }

            cout << "Territories to defend: " << endl;
            for(Territory* t : this->to_defend())
            {
                if(sourceTerritoryToNumberMap[sourceTerritoryChoice]->borders_territory(t))
                {
                    destinationTerritoryToNumberMap[counter2] = t;
                    cout << counter2 << ": " << t->get_name() << " (" << t->get_armies() << " troops)" << endl;
                    counter2++;
                }
            }

            // Read input and validate it.
            int destinationTerritoryChoice = -1;
            while(destinationTerritoryChoice<0 || destinationTerritoryChoice > destinationTerritoryToNumberMap.size())
                cin >> destinationTerritoryChoice;

            Advance* advanceOrder = new Advance(generator.setID(), troopNumber, sourceTerritoryToNumberMap.at(sourceTerritoryChoice), destinationTerritoryToNumberMap.at(destinationTerritoryChoice), this);
            addOrder(advanceOrder);

            cout << "Advance order issued." << endl;
            break;
        }
        case 2:
        {
            // Play a card

            cout << "Which card would you like to play?" << endl;

            int counter = 0;
            std::map<int, Card*> cardsToNumbers = std::map<int, Card*>();

            // Creating an iterator
            std::list<Card>::iterator iterator;
            // Iterating through the hand
            for (iterator = hand->cards->begin(); iterator != hand->cards->end(); ++iterator) {
                cardsToNumbers[counter] = &*iterator;
                cout<< counter << ": " << iterator->toString() << endl;
                counter++;
            }

            // Read input and validate it.
            int cardChoice = -1;
            while(cardChoice < 0 || cardChoice > hand->remainingCards())
                cin >> cardChoice;

            // Playing the card.
            Card* card = cardsToNumbers[cardChoice];

            cout << "Playing a card: " + card->toString() << endl;

            card->playHuman(this, deck, territoriesMap, gamePlayers);
            break;
        }
        case 3:
            cout << "Ending turn." << endl;
            return false;
        default:
            throw exception("Invalid action chosen for a player's turn.");
    }
    return true;
}


vector<Territory *> Player::to_defend() {
    return territories;
}

vector<Territory *> Player::to_attack() {
    std::set<Territory*> territoriesToAttack = set<Territory*>();

    // Loop through all our territories...
    for(Territory* t : this->territories)
    {
        // ... finding every adjacent territories...
        for(Territory* adj : t->get_bordering_territory())
        {
            // ... that aren't ours.
            if(adj->getPlayer() != this)
                territoriesToAttack.emplace(adj);
        }
    }

    // Transforming the set to a vector.
    vector<Territory*> setToVector = vector<Territory*>();

    setToVector.reserve(territoriesToAttack.size());
    for(Territory* t : territoriesToAttack)
    {
        setToVector.push_back(t);
    }
    return setToVector;
}

OrdersList* Player::getOrdersList() {
    return orders;
}

void Player::addFriendlyPlayer(Player* player) {
    friendlyPlayers.push_back(player);
}

bool Player::isFriendly(Player *player) {
    for (int i = 0; i < friendlyPlayers.size(); i++){
        if (player->name.compare(friendlyPlayers.at(i)->name) == 0)
            return true;
    }
    return false;
}

bool Player::hasConquered() {
    return conquered;
}

void Player::setConquered(bool conquered) {
    this->conquered = conquered;
}

/* Overloads */
//stream insertion operator
ostream &operator<<(std::ostream &strm, const Player &player) {
    strm << "Player Object Data:\n";
    strm << player.name << "\n";
    strm << "Territories \n";
    for (Territory *territory: player.territories) {
        strm << *territory;
    }
    strm << "Orders \n";
    strm << *player.orders;
    strm << "Cards \n";
    for (const Card& card: *player.hand->cards) {
        strm << card << "\n";
    }

    return strm;
}

// assignment operator
Player& Player::operator=(const Player& p) {
    for (Territory *territory: territories) {
        delete territory;
    }
    delete orders;
    for (Player* player: friendlyPlayers){
        delete player;
    }
    delete hand;
    this->territories = p.territories;
    this->orders = p.orders;
    this->hand = p.hand;
    this->conquered = p.conquered;
    this->orderOfPlay = p.orderOfPlay;
    this->friendlyPlayers = p.friendlyPlayers;

    return *this;
}

// Player comparator
bool Player::operator<(const Player &other) const {
        return orderOfPlay < other.orderOfPlay;
}


