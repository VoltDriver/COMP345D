#include <iostream>
#include <map>
#include <set>
#include <random>

#include "Player.h"
#include "PlayerStrategies.h"
#include "Orders.h"


/* PlayerStrategy class */
PlayerStrategy::PlayerStrategy() {}
PlayerStrategy::~PlayerStrategy() {}

void PlayerStrategy::setStrategyName(string name) {
    strategy_name = name;
}

string PlayerStrategy::getStrategyName() {
    return strategy_name;
}



/* DefaultPlayerStrategy class */
DefaultPlayerStrategy::DefaultPlayerStrategy() {
    setStrategyName("Default");
}
DefaultPlayerStrategy::~DefaultPlayerStrategy() {}

vector<Territory*> DefaultPlayerStrategy::to_defend(Player *player) {
    return player->getTerritories();
}

vector<Territory*> DefaultPlayerStrategy::to_attack(Player *player) {
    std::set<Territory*> territoriesToAttack = set<Territory*>();

    // Loop through all our territories...
    for(Territory* t : player->getTerritories())
    {
        // ... finding every adjacent territories...
        for(Territory* adj : t->get_bordering_territory())
        {
            // ... that aren't ours.
            if(adj->getPlayer() != player)
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

bool DefaultPlayerStrategy::issueOrder(Player *player, Deck* deck, Map* territoriesMap,const list<Player*> gamePlayers) {
    int actionNumber = -1;

    // We use Mt19937 and random_device, which seeds the random generator with some random data from the system.
    // There's other ways to do it, but this is efficient and does not require seeding with Time.
    std::random_device randomDevice;
    std::mt19937 mt(randomDevice());

    // ID Generator
    ID generator = ID();

    // If some reinforcements are left in the pool of the player, he can only take deploy actions.
    if(player->getUncommittedReinforcementPool() > 0)
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
        for(Territory* t : player->getTerritories())
        {
            if(t->get_armies() > 0)
                advanceAllowed = true;
        }

        if(advanceAllowed)
            possibleActions.push_back(1);

        // Play a card
        if(player->getHand()->remainingCards() > 0)
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
            for(Territory* t : player->to_defend()) //********************
            {
                territoryToNumberMap[counter] = t;
                counter++;
            }

            // Generate a random input
            std::uniform_int_distribution<int> distribution(0,territoryToNumberMap.size() - 1);

            int territoryChoice = distribution(mt);

            // Generate a random input
            std::uniform_int_distribution<int> distributionTroops(1,player->getUncommittedReinforcementPool());
            int troopNumber = distributionTroops(mt);

            auto* deployOrder = new Deploy(generator.setID(), troopNumber, territoryToNumberMap[territoryChoice], player);
            player->addOrder(deployOrder);

            cout << "Deploy order issued." << endl;

            // Adjust the uncommitted reinforcement pool.
            player->setUncommittedReinforcementPool(player->getUncommittedReinforcementPool() - troopNumber);
            break;
        }
        case 1:
        {
            // Advance

            // Choosing a starting point
            std::map<int, Territory*> sourceTerritoryToNumberMap = map<int, Territory*>();
            int counter = 0;

            for(Territory* t : player->to_defend())
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
            for(Territory* t : player->to_attack())
            {
                if(sourceTerritoryToNumberMap[sourceTerritoryChoice]->borders_territory(t))
                {
                    destinationTerritoryToNumberMap[counter2] = t;
                    counter2++;
                }
            }
            // Advancing to defend
            for(Territory* t : player->to_defend())
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

            Advance* advanceOrder = new Advance(generator.setID(), troopNumber, sourceTerritoryToNumberMap.at(sourceTerritoryChoice), destinationTerritoryToNumberMap.at(destinationTerritoryChoice), player);
            player->addOrder(advanceOrder);

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
            for (iterator = player->hand->cards->begin(); iterator != player->hand->cards->end(); ++iterator) {
                cardsToNumbers[counter] = &*iterator;
                counter++;
            }

            // Generate a random input
            std::uniform_int_distribution<int> distribution(0, player->hand->remainingCards() - 1);
            int cardChoice = distribution(mt);

            // Playing the card.
            Card* card = cardsToNumbers[cardChoice];

            cout << "Playing a card: " + card->toString() << endl;
            card->play(player, deck, territoriesMap, gamePlayers);
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



/* HumanPlayerStrategy class */
HumanPlayerStrategy::HumanPlayerStrategy() {
    setStrategyName("Human");
}
HumanPlayerStrategy::~HumanPlayerStrategy() {}
vector<Territory*> HumanPlayerStrategy::to_defend(Player* player) {
    return player->getTerritories();
}

vector<Territory*> HumanPlayerStrategy::to_attack(Player* player) {
    std::set<Territory*> territoriesToAttack = set<Territory*>();

    // Loop through all our territories...
    for(Territory* t : player->getTerritories())
    {
        // ... finding every adjacent territories...
        for(Territory* adj : t->get_bordering_territory())
        {
            // ... that aren't ours.
            if(adj->getPlayer() != player)
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

bool HumanPlayerStrategy::issueOrder(Player *player, Deck* deck, Map* territoriesMap,const list<Player*> gamePlayers) {
    int nbOfPossibleActions = 4;
    int actionNumber = -1;

    cout << player->name << ", which order would you like to issue? (input the number)" << endl;
    cout << "List of possible orders:" << endl;

    // ID Generator
    ID generator = ID();

    // If some reinforcements are left in the pool of the player, he can only take deploy actions.
    if(player->getUncommittedReinforcementPool() > 0)
    {
        // Deploy
        cout << "0: Deploy " << endl;
        cout << "(You have " << player->getUncommittedReinforcementPool() << " reinforcements left in your pool. You must deploy them before issuing any other order." << endl;

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
        for(Territory* t : player->getTerritories())
        {
            if(t->get_armies() > 0)
                advanceAllowed = true;
        }

        if(advanceAllowed) {
            possibleActions.push_back(1);
        }

        // Play a card
        if(player->hand->remainingCards() > 0)
        {
            possibleActions.push_back(2);
            cout << "2: Play a card" << endl;
        }

        // End turn
        possibleActions.push_back(3);
        cout << "3: End your turn." << endl;

        // Validate input.
        while(actionNumber<0 ||
              actionNumber >= nbOfPossibleActions ||
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
            for(Territory* t : this->to_defend(player))
            {
                territoryToNumberMap[counter] = t;

                cout << counter << ": " << t->get_name() << " (" << t->get_armies() << " troops)" << endl;
                counter++;
            }

            // Read input and validate it.
            int territoryChoice = -1;
            while(territoryChoice<0 || territoryChoice > this->to_defend(player).size())
                cin >> territoryChoice;

            cout << "How many troops would you like to deploy? (" << player->getUncommittedReinforcementPool() << " remaining in your reinforcement pool.)" << endl;

            // Read input and validate it.
            int troopNumber = -1;
            while(troopNumber<0 || troopNumber > player->getUncommittedReinforcementPool())
                cin >> troopNumber;

            auto* deployOrder = new Deploy(generator.setID(), troopNumber, territoryToNumberMap[territoryChoice], player);
            player->addOrder(deployOrder);

            cout << "Deploy order issued." << endl;

            // Adjust the uncommitted reinforcement pool
            player->setUncommittedReinforcementPool(player->getUncommittedReinforcementPool() - troopNumber);
            break;
        }
        case 1:
        {
            // Advance

            // List the territories the player can choose as starting point
            cout << "From which territory would you like to select troops from?"<< endl;
            std::map<int, Territory*> sourceTerritoryToNumberMap = map<int, Territory*>();
            int counter = 0;
            for(Territory* t : this->to_defend(player))
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
            while(sourceTerritoryChoice<0 || sourceTerritoryChoice > this->to_defend(player).size())
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
            for(Territory* t : this->to_attack(player))
            {
                if(sourceTerritoryToNumberMap[sourceTerritoryChoice]->borders_territory(t))
                {
                    destinationTerritoryToNumberMap[counter2] = t;
                    cout << counter2 << ": " << t->get_name() << " (" << t->get_armies() << " troops)" << endl;
                    counter2++;
                }
            }

            cout << "Territories to defend: " << endl;
            for(Territory* t : this->to_defend(player))
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

            Advance* advanceOrder = new Advance(generator.setID(), troopNumber, sourceTerritoryToNumberMap.at(sourceTerritoryChoice), destinationTerritoryToNumberMap.at(destinationTerritoryChoice), player);
            player->addOrder(advanceOrder);

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
            for (iterator = player->hand->cards->begin(); iterator != player->hand->cards->end(); ++iterator) {
                cardsToNumbers[counter] = &*iterator;
                cout<< counter << ": " << iterator->toString() << endl;
                counter++;
            }

            // Read input and validate it.
            int cardChoice = -1;
            while(cardChoice < 0 || cardChoice > player->hand->remainingCards())
                cin >> cardChoice;

            // Playing the card.
            Card* card = cardsToNumbers[cardChoice];

            cout << "Playing a card: " + card->toString() << endl;

            card->playHuman(player, deck, territoriesMap, gamePlayers);
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



/* AggressivePlayerStrategy class */
AggressivePlayerStrategy::AggressivePlayerStrategy() {
    setStrategyName("Aggressive");
    strongestTerritory = nullptr;
    advanceAllowed = true;
}

AggressivePlayerStrategy::~AggressivePlayerStrategy() {}


Territory* AggressivePlayerStrategy::getStrongestTerritory() {
    return strongestTerritory;
}

void AggressivePlayerStrategy::setStrongestTerritory(Player* player) {
    this->strongestTerritory = player->getTerritories()[0];
    for (int i = 0; i < player->getTerritories().size(); i++) {
        if (this->strongestTerritory->get_armies() < player->getTerritories()[i]->get_armies())
            this->strongestTerritory = player->getTerritories()[i];
    }
}

vector<Territory*> AggressivePlayerStrategy::to_defend(Player *player) {
    return player->getTerritories();
}

vector<Territory*> AggressivePlayerStrategy::to_attack(Player *player) {
    std::set<Territory*> territoriesToAttack = set<Territory*>();

    // Loop through all our territories...
    for(Territory* t : player->getTerritories())
    {
        // ... finding every adjacent territories...
        for(Territory* adj : t->get_bordering_territory())
        {
            // ... that aren't ours.
            if(adj->getPlayer() != player)
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

bool AggressivePlayerStrategy::issueOrder(Player *player, Deck* deck, Map* territoriesMap,const list<Player*> gamePlayers) {
    int actionNumber = -1;

    // We use Mt19937 and random_device, which seeds the random generator with some random data from the system.
    // There's other ways to do it, but this is efficient and does not require seeding with Time.
    std::random_device randomDevice;
    std::mt19937 mt(randomDevice());

    // ID Generator
    ID generator = ID();
    setStrongestTerritory(player);
    // If some reinforcements are left in the pool of the player, he can only take deploy actions.
    if (player->getUncommittedReinforcementPool() > 0) {
        advanceAllowed = true;
        cout << "You have reinforcements in your pool. Only deploy orders are allowed." << endl;
        // Deploy
        actionNumber = 0;
    } else {
        list<int> possibleActions = list<int>();

        // Advance
        if (advanceAllowed) {
            possibleActions.push_back(1);
        }

        // Play a card
        if(player->getHand()->remainingCards() > 0)
            possibleActions.push_back(2);

        // End turn
        possibleActions.push_back(3);

        // Generate a random input
        std::uniform_int_distribution<int> distribution(0, possibleActions.size() - 1);

        auto iterator = std::next(possibleActions.begin(), distribution(mt));
        actionNumber = *iterator;
    }

    // Depending on which action was chosen, create an appropriate order.
    switch (actionNumber) {
        case 0: {
            // Deploy

            // Choose a territory

            // Generate a random input
            std::uniform_int_distribution<int> distributionTroops(1, player->getUncommittedReinforcementPool());
            int troopNumber = distributionTroops(mt);

            auto *deployOrder = new Deploy(generator.setID(), troopNumber, strongestTerritory, player);
            player->addOrder(deployOrder);

            cout << "Deploy order issued." << endl;

            // Adjust the uncommitted reinforcement pool.
            player->setUncommittedReinforcementPool(player->getUncommittedReinforcementPool() - troopNumber);
            break;
        }
        case 1: {

            // Advance

            // Choosing a starting point
            for (int i = 0; i < to_defend(player).size(); i++) {
                int sourceTerritoryChoice = i;

                // Choosing randomly a number of troops to move;

                int troopNumber = to_defend(player)[sourceTerritoryChoice]->get_armies();
                if (troopNumber > 0) {
                    // Choose a territory for the player to advance to.
                    std::map<int, Territory *> destinationTerritoryToNumberMap = map<int, Territory *>();
                    int counter2 = 0;

                    for (int j = 0;
                         j < to_defend(player)[sourceTerritoryChoice]->get_bordering_territory().size(); j++) {
                        if (to_defend(player)[sourceTerritoryChoice]->get_bordering_territory()[j]->getPlayer() == nullptr || player->name.compare(
                                to_defend(player)[sourceTerritoryChoice]->get_bordering_territory()[j]->getPlayerName()) !=0){
                            destinationTerritoryToNumberMap[counter2] = to_defend(
                                    player)[sourceTerritoryChoice]->get_bordering_territory()[j];
                            counter2++;
                        }
                    }

                    if (destinationTerritoryToNumberMap.size() == 0) {
                        if (to_defend(player)[i]->get_id() == strongestTerritory->get_id()) {
                            std::uniform_int_distribution<int> distributionDestination(0,
                                                                                       strongestTerritory->get_bordering_territory().size() -
                                                                                       1);
                            int destinationTerritoryChoice = distributionDestination(mt);
                            Advance *advanceOrder = new Advance(generator.setID(), troopNumber,
                                                                to_defend(player).at(sourceTerritoryChoice),
                                                                strongestTerritory->get_bordering_territory()[destinationTerritoryChoice],
                                                                player);
                            player->addOrder(advanceOrder);
                        }
                        else{
                            Advance *advanceOrder = new Advance(generator.setID(), troopNumber,
                                                                to_defend(player).at(
                                                                        sourceTerritoryChoice),
                                                                strongestTerritory,
                                                                player);
                            player->addOrder(advanceOrder);
                        }
                    } else {
                        std::uniform_int_distribution<int> distributionDestination(0,
                                                                                   destinationTerritoryToNumberMap.size() -
                                                                                   1);
                        int destinationTerritoryChoice = distributionDestination(mt);
                        Advance *advanceOrder = new Advance(generator.setID(), troopNumber,
                                                            to_defend(player).at(sourceTerritoryChoice),
                                                            destinationTerritoryToNumberMap[destinationTerritoryChoice],
                                                            player);
                        player->addOrder(advanceOrder);
                    }
                }
            }
            advanceAllowed = false;
            break;
        }
        case 2: {
            // Play a card

            int counter = 0;
            std::map<int, Card *> cardsToNumbers = std::map<int, Card *>();

            // Creating an iterator
            std::list<Card>::iterator iterator;
            // Iterating through the hand
            for (iterator = player->hand->cards->begin(); iterator != player->hand->cards->end(); ++iterator) {
                    cardsToNumbers[counter] = &*iterator;
                    counter++;
            }

            // Generate a random input
            if (counter > 0) {
                std::uniform_int_distribution<int> distribution(0, player->hand->remainingCards() - 1);
                int cardChoice = distribution(mt);

                // Playing the card.
                Card *card = cardsToNumbers[cardChoice];

                cout << "Playing a card: " + card->toString() << endl;
                card->play(player, deck, territoriesMap, gamePlayers);
            }
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




//BenevolentPlayerStrategy class
BenevolentPlayerStrategy::BenevolentPlayerStrategy() {
    setStrategyName("Benevolent");
    weakestTerritory = nullptr;
    weakestTerritories = vector<Territory*>();
}

BenevolentPlayerStrategy::~BenevolentPlayerStrategy() {}

Territory* BenevolentPlayerStrategy::getWeakestTerritory() {
    return weakestTerritory;
}

vector<Territory*> BenevolentPlayerStrategy::getWeakestTerritories(Player *player){
    weakestTerritories.clear();
    this->weakestTerritory = player->getTerritories()[0];
    for (int i = 0; i < player->getTerritories().size(); i++) {
        if (this->weakestTerritory->get_armies() > player->getTerritories()[i]->get_armies())
            this->weakestTerritory = player->getTerritories()[i];
    }
    weakestTerritories.push_back(this->weakestTerritory);
    for (Territory *t: player->getTerritories()) {
    if (t->get_armies() == this->weakestTerritory->get_armies())
        weakestTerritories.push_back(t);
    }
    return weakestTerritories;
}

vector<Territory*> BenevolentPlayerStrategy::to_defend(Player *player) {
    return player->getTerritories();
}

vector<Territory*> BenevolentPlayerStrategy::to_attack(Player *player) {
    std::set<Territory*> territoriesToAttack = set<Territory*>();

    // Loop through all our territories...
    for(Territory* t : player->getTerritories())
    {
        // ... finding every adjacent territories...
        for(Territory* adj : t->get_bordering_territory())
        {
            // ... that aren't ours.
            if(adj->getPlayer() != player)
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

bool BenevolentPlayerStrategy::issueOrder(Player *player, Deck* deck, Map* territoriesMap,const list<Player*> gamePlayers) {
    int actionNumber = -1;

    // We use Mt19937 and random_device, which seeds the random generator with some random data from the system.
    // There's other ways to do it, but this is efficient and does not require seeding with Time.
    std::random_device randomDevice;
    std::mt19937 mt(randomDevice());

    // ID Generator
    ID generator = ID();

    // If some reinforcements are left in the pool of the player, he can only take deploy actions.
    if(player->getUncommittedReinforcementPool() > 0)
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
        getWeakestTerritories(player);
        for(Territory* t : player->getTerritories())
        {
            if(t->get_armies() > weakestTerritory->get_armies())
                advanceAllowed = true;
        }

        if(advanceAllowed) {
            possibleActions.push_back(1);
            cout << "1: Advance " << endl;
        }

        // Play a card
        if(player->getHand()->remainingCards() > 0)
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
            for(Territory* t : getWeakestTerritories(player)) //********************
            {
                territoryToNumberMap[counter] = t;
                counter++;
            }

            // Generate a random input
            std::uniform_int_distribution<int> distribution(0,territoryToNumberMap.size() - 1);

            int territoryChoice = distribution(mt);

            // Generate a random input
            std::uniform_int_distribution<int> distributionTroops(1,player->getUncommittedReinforcementPool());
            int troopNumber = distributionTroops(mt);

            auto* deployOrder = new Deploy(generator.setID(), troopNumber, territoryToNumberMap[territoryChoice], player);
            player->addOrder(deployOrder);

            cout << "Deploy order issued." << endl;

            // Adjust the uncommitted reinforcement pool.
            player->setUncommittedReinforcementPool(player->getUncommittedReinforcementPool() - troopNumber);
            break;
        }
        case 1:
        {
            // Advance

            // Choosing a starting point
            std::map<int, Territory*> sourceTerritoryToNumberMap = map<int, Territory*>();
            int counter = 0;
            for(Territory* t : player->getTerritories())
            {
                // We can choose a starting point only if it has any armies.
                if(t->get_armies() > weakestTerritory->get_armies())
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

            // Advancing to defend
            for(Territory* t : weakestTerritories)
            {
                if(sourceTerritoryToNumberMap[sourceTerritoryChoice]->borders_territory(t))
                {
                    destinationTerritoryToNumberMap[counter2] = t;
                    counter2++;
                }
            }

            // Choosing randomly a territory to move to
            if (destinationTerritoryToNumberMap.size() != 0) {
                std::uniform_int_distribution<int> distributionDestination(0,
                                                                           destinationTerritoryToNumberMap.size() - 1);

                int destinationTerritoryChoice = distributionDestination(mt);

                Advance *advanceOrder = new Advance(generator.setID(), troopNumber,
                                                    sourceTerritoryToNumberMap.at(sourceTerritoryChoice),
                                                    destinationTerritoryToNumberMap.at(destinationTerritoryChoice),
                                                    player);
                player->addOrder(advanceOrder);

                cout << "Advance order issued." << endl;
            }
            else{
                cout << "This territory does not border your weakest territories" << endl;
            }
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
            for (iterator = player->hand->cards->begin(); iterator != player->hand->cards->end(); ++iterator) {
                if (*iterator->type != Bomb) {
                    cardsToNumbers[counter] = &*iterator;
                    counter++;
                }
            }

            // Generate a random input
            std::uniform_int_distribution<int> distribution(0, player->hand->remainingCards() - 1);
            int cardChoice = distribution(mt);

            // Playing the card.
            Card* card = cardsToNumbers[cardChoice];

            cout << "Playing a card: " + card->toString() << endl;
            card->play(player, deck, territoriesMap, gamePlayers);
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



/* NeutralPlayerStrategy class */
NeutralPlayerStrategy::NeutralPlayerStrategy() {
    setStrategyName("Neutral");
}
NeutralPlayerStrategy::~NeutralPlayerStrategy() {}

vector<Territory*> NeutralPlayerStrategy::to_defend(Player *player) {
    return player->getTerritories();
}

vector<Territory*> NeutralPlayerStrategy::to_attack(Player *player) {
    std::set<Territory*> territoriesToAttack = set<Territory*>();

    // Loop through all our territories...
    for(Territory* t : player->getTerritories())
    {
        // ... finding every adjacent territories...
        for(Territory* adj : t->get_bordering_territory())
        {
            // ... that aren't ours.
            if(adj->getPlayer() != player)
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

bool NeutralPlayerStrategy::issueOrder(Player *player, Deck* deck, Map* territoriesMap,const list<Player*> gamePlayers) {
    cout << "Ending turn.\n" << endl;
    return false;
}


