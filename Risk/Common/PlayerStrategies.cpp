#include <iostream>
#include <map>
#include <set>
#include <random>

#include "Player.h"
#include "PlayerStrategies.h"


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
//HumanPlayerStrategy::HumanPlayerStrategy() {}
//HumanPlayerStrategy::~HumanPlayerStrategy() {}
//vector<Territory*> HumanPlayerStrategy::to_defend() {
//
//}
//
//vector<Territory*> HumanPlayerStrategy::to_attack() {
//
//}
//
//bool HumanPlayerStrategy::issueOrder(Deck* deck, Map* territoriesMap,const list<Player*> gamePlayers) {
//
//}



/* AggressivePlayerStrategy class */
//AggressivePlayerStrategy::AggressivePlayerStrategy() {}
//AggressivePlayerStrategy::~AggressivePlayerStrategy() {}
//vector<Territory*> AggressivePlayerStrategy::to_defend() {
//
//}
//
//vector<Territory*> AggressivePlayerStrategy::to_attack() {
//
//}
//
//bool AggressivePlayerStrategy::issueOrder(Deck* deck, Map* territoriesMap,const list<Player*> gamePlayers) {
//
//}



/* BenevolentPlayerStrategy class */
//BenevolentPlayerStrategy::BenevolentPlayerStrategy() {}
//BenevolentPlayerStrategy::~BenevolentPlayerStrategy() {}
//vector<Territory*> BenevolentPlayerStrategy::to_defend() {
//
//}
//
//vector<Territory*> BenevolentPlayerStrategy::to_attack() {
//
//}
//
//bool BenevolentPlayerStrategy::issueOrder(Deck* deck, Map* territoriesMap,const list<Player*> gamePlayers) {
//
//}



/* NeutralPlayerStrategy class */
//NeutralPlayerStrategy::NeutralPlayerStrategy() {}
//NeutralPlayerStrategy::~NeutralPlayerStrategy() {}
//vector<Territory*> NeutralPlayerStrategy::to_defend() {
//
//}
//
//vector<Territory*> NeutralPlayerStrategy::to_attack() {
//
//}
//
//bool NeutralPlayerStrategy::issueOrder(Deck* deck, Map* territoriesMap,const list<Player*> gamePlayers) {
//
//}

