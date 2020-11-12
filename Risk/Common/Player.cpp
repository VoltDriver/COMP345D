#include <iostream>
#include <string>
#include <map>
#include "Player.h"
#include "Cards.h"
#include "Orders.h"

// Number of Possible actions the user can take
const int NUMBER_OF_POSSIBLE_ACTIONS = 4;

// default constructor
Player::Player() {
    this->territories = vector<Territory*>();
    this->orders = vector<Order*>();
    this->hand = new Hand();
    this->name = "";
    this->reinforcementPool = 0;
}

// parameterized constructors
Player::Player(string name) {
    this->territories = vector<Territory*>();
    this->orders = vector<Order*>();
    this->hand = new Hand();
    this->name = name;
    this->reinforcementPool = 0;
}

Player::Player(vector<Territory*> territories, vector<Order*> orders, Hand* hand) {
    this->territories = territories;
    this->orders = orders;
    this->hand = hand;
    this->name = "";
    this->reinforcementPool = 0;
}

Player::Player(vector<Territory*> territories, vector<Order*> orders, Hand* hand, string name) {
    this->territories = territories;
    this->orders = orders;
    this->hand = hand;
    this->name = name;
    this->reinforcementPool = 0;
}

// copy constructor
Player::Player(const Player &p) {
    this->territories = p.territories;
    this->orders = p.orders;
    this->hand = p.hand;
    this->name = p.name;
    this->reinforcementPool = p.reinforcementPool;
}


/* Destructor */
Player::~Player() {
    for (Territory *territory: territories) {
        delete territory;
    }
    for (Order *order: orders) {
        delete order;
    }
    delete hand;
}


/* Methods */
void Player::addOrder(Order* order) {
    orders.push_back(order);
    cout << "order has been added to list of orders" << endl;
}

/**
 * Prompts the player to issue an order.
 * @return True if an order was issued, false otherwise.
 */
bool Player::issueOrder(Deck* deck) {
    int actionNumber = -1;

    cout << this->name << ", which order would you like to issue? (input the number)" << endl;
    cout << "List of possible orders:" << endl;

    // If some reinforcements are left in the pool of the player, he can only take deploy actions.
    if(this->reinforcementPool > 0)
    {
        cout << "0: Deploy " << endl;
        cout << "(You have " << this->reinforcementPool << " reinforcements left in your pool. You must deploy them before issuing any other order." << endl;

        // Validate input.
        while(actionNumber != 0)
            cin >> actionNumber;
    }
    else
    {
        cout << "0: Deploy " << endl;
        cout << "1: Advance " << endl;
        cout << "2: Play a card" << endl;
        cout << "3: End your turn." << endl;

        // Validate input.
        while(actionNumber<0 || actionNumber >= NUMBER_OF_POSSIBLE_ACTIONS)
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

            cout << "How many troops would you like to deploy? (" << this->reinforcementPool << " remaining in your reinforcement pool.)" << endl;

            // Read input and validate it.
            int troopNumber = -1;
            while(troopNumber<0 || troopNumber > this->reinforcementPool)
                cin >> troopNumber;

            // TODO: Create the order properly... And implement a constructor that makes them automatically.
            Deploy* deployOrder = new Deploy(0);
            addOrder(deployOrder);

            cout << "Deploy order issued." << endl;
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
                sourceTerritoryToNumberMap[counter] = t;

                cout << counter << ": " << t->get_name() << " (" << t->get_armies() << " troops)" << endl;
                counter++;
            }

            // Read input and validate it.
            int sourceTerritoryChoice = -1;
            while(sourceTerritoryChoice<0 || sourceTerritoryChoice > to_defend().size())
                cin >> sourceTerritoryChoice;

            cout << "How many troops would you like to move? (" << sourceTerritoryToNumberMap[sourceTerritoryChoice]->get_armies() << " remaining in your territory.)" << endl;

            // Read input and validate it.
            int troopNumber = -1;
            while(troopNumber<0 || troopNumber > this->reinforcementPool)
                cin >> troopNumber;

            // List the territories the player can choose to advance to
            cout << "To which territory would you like to advance your troops to?"<< endl;
            std::map<int, Territory*> destinationTerritoryToNumberMap = map<int, Territory*>();
            int counter2 = 0;

            // TODO: Differentiate between friendly territories and enemy territories, and use toAttack() method.
            for(Territory* t : sourceTerritoryToNumberMap[sourceTerritoryChoice]->get_bordering_territory())
            {
                destinationTerritoryToNumberMap[counter2] = t;

                cout << counter2 << ": " << t->get_name() << " (" << t->get_armies() << " troops)" << endl;
                counter2++;
            }

            // Read input and validate it.
            int destinationTerritoryChoice = -1;
            while(destinationTerritoryChoice<0 || destinationTerritoryChoice > to_defend().size())
                cin >> destinationTerritoryChoice;

            // TODO: Create the order properly... And implement a constructor that makes them automatically.
            Advance* advanceOrder = new Advance(0);
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

            card->play(this, deck);
            break;
        }
        case 3:
            return false;
        default:
            throw exception("Invalid action chosen for a player's turn.");
    }
}

vector<Territory *> Player::to_defend() {
    return territories;
}

vector<Territory *> Player::to_attack() {
    return territories;
}

int Player::getReinforcementPool() {
    return reinforcementPool;
}

/* Overloaders */
//stream insertion operator
ostream &operator<<(std::ostream &strm, const Player &player) {
    strm << "Player Object Data:\n";
    strm << "Territories \n";
    for (Territory *territory: player.territories) {
        strm << *territory;
    }
    strm << "Orders \n";
    for (Order *order: player.orders) {
        strm << order->description << "\n";
    }
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
    for (Order *order: orders) {
        delete order;
    }
    delete hand;
    this->territories = p.territories;
    this->orders = p.orders;
    this->hand = p.hand;

    return *this;
}