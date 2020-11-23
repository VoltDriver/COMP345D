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



/* DefaultPlayerStrategy class */
DefaultPlayerStrategy::DefaultPlayerStrategy() {}
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
HumanPlayerStrategy::HumanPlayerStrategy() {}
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
            cout << "1: Advance " << endl;
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
//AggressivePlayerStrategy::AggressivePlayerStrategy() {}
//AggressivePlayerStrategy::~AggressivePlayerStrategy() {}
//vector<Territory*> AggressivePlayerStrategy::to_defend(Player *player) {
//
//}
//
//vector<Territory*> AggressivePlayerStrategy::to_attack(Player *player) {
//
//}
//
//bool AggressivePlayerStrategy::issueOrder(Player *player, Deck* deck, Map* territoriesMap,const list<Player*> gamePlayers) {
//
//}



/* BenevolentPlayerStrategy class */
//BenevolentPlayerStrategy::BenevolentPlayerStrategy() {}
//BenevolentPlayerStrategy::~BenevolentPlayerStrategy() {}
//vector<Territory*> BenevolentPlayerStrategy::to_defend(Player *player) {
//
//}
//
//vector<Territory*> BenevolentPlayerStrategy::to_attack(Player *player) {
//
//}
//
//bool BenevolentPlayerStrategy::issueOrder(Player *player, Deck* deck, Map* territoriesMap,const list<Player*> gamePlayers) {
//
//}



/* NeutralPlayerStrategy class */
//NeutralPlayerStrategy::NeutralPlayerStrategy() {}
//NeutralPlayerStrategy::~NeutralPlayerStrategy() {}
//vector<Territory*> NeutralPlayerStrategy::to_defend(Player *player) {
//
//}
//
//vector<Territory*> NeutralPlayerStrategy::to_attack(Player *player) {
//
//}
//
//bool NeutralPlayerStrategy::issueOrder(Player *player, Deck* deck, Map* territoriesMap,const list<Player*> gamePlayers) {
//
//}

