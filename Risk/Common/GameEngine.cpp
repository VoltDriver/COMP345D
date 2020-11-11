#include "GameEngine.h"

/// Constitutes the minimum amount of reinforcement per turn per player.
const int MINIMUM_REINFORCEMENT = 3;

// Continent_ArmyBonus_OwnedTerritories_DataObject

ContinentOwnership_DataObject::ContinentOwnership_DataObject()
{
    continent = nullptr;
    armyBonus = 0;
    ownedTerritories = 0;
}
ContinentOwnership_DataObject::ContinentOwnership_DataObject(Continent* c, int ab, int ot)
{
    continent = c;
    armyBonus = ab;
    ownedTerritories = ot;
}

void GameEngine::mainGameLoop() {
    bool gameOver = false;
    string winningPlayer = "";

    while(!gameOver)
    {
        // Reinforcement Phase
        reinforcementPhase();

        // Issuing Orders Phase
        issueOrdersPhase();

        // Orders Execution Phase
        executeOrdersPhase();

        // Checking if the game is over
        for(Player player : players)
        {
            if(player.territories.size() == map->get_territories().size())
            {
                gameOver = true;
                winningPlayer = player.name;
            }
        }

        // Checking if a player has lost
        auto it = players.begin();
        while(it != players.end())
        {
            auto current = it++;
            if(current->territories.empty())
            {
                cout << current->name << " has lost!";
                players.erase(current);
            }
        }
    }

    cout << "The game is over! " << winningPlayer << " has won.";
}

void GameEngine::reinforcementPhase() {
    for(Player& player : players)
    {
        int reinforcement = 0;

        int nbTerritoriesOwned = player.territories.size();

        // Int division because it is rounded down.
        reinforcement += nbTerritoriesOwned / 3;

        std::map<string, ContinentOwnership_DataObject> continentOwnership = std::map<string, ContinentOwnership_DataObject>();

        for(Territory* t : player.territories)
        {
            ContinentOwnership_DataObject ownership;

            // Checking if the continent is already part of the map
            if(continentOwnership.find(t->get_continent()->get_name()) == continentOwnership.end())
            {
                // ... if it's not there, then we add it in.
                continentOwnership[t->get_continent()->get_name()] = ContinentOwnership_DataObject(t->get_continent(),
                                                                                                       t->get_continent()->get_army_bonus(),
                                                                                                       0);
            }

            // Adding 1 to the amount of territories owned of that continent.
            continentOwnership[t->get_continent()->get_name()].ownedTerritories += 1;
        }

        // Now calculating the Army Bonus for whole continent ownership
        for(auto& entry : continentOwnership)
        {
            if(entry.second.continent->get_territories().size() == entry.second.ownedTerritories)
            {
                reinforcement += entry.second.armyBonus;
            }
        }

        // Ensuring the minimum reinforcement rule is applied
        if(reinforcement < MINIMUM_REINFORCEMENT)
        {
            reinforcement = MINIMUM_REINFORCEMENT;
        }

        // Place the reinforcements in the players' pools.
        player.reinforcementPool += reinforcement;
    }
}

void GameEngine::issueOrdersPhase() {

    // Contains whether a player is done with their turn or not. True if not done.
    std::map<string, bool> playerTurns = std::map<string, bool>();

    // Initializing the map
    for(Player& player : players)
    {
        playerTurns[player.name] = true;
    }

    // Going round robin until all turns are done.
    int amountOfPlayersDone = 0;

    while(amountOfPlayersDone != players.size())
    {
        for(Player& player : players)
        {
            // If a player did not end his turn yet...
            if(playerTurns[player.name])
            {
                // ... it is prompted to play.
                playerTurns[player.name] = player.issueOrder(this->deck);

                // If it decided to end it's turn just now...
                if(!playerTurns[player.name])
                {
                    // ... we add it to the number of players that are done.
                    amountOfPlayersDone++;
                }
            }
        }
    }

    // Everyone has played.
}

void GameEngine::executeOrdersPhase() {
    // Contains whether a player is done with their orders or not. True if not done.
    std::map<string, bool> playerOrdersStatus = std::map<string, bool>();

    // Initializing the map
    for(Player& player : players)
    {
        playerOrdersStatus[player.name] = true;
    }

    // Going round robin until all orders are done.
    int amountOfPlayersDone = 0;

    while(amountOfPlayersDone != players.size())
    {
        for(Player& player : players)
        {
            // If a player still has orders...
            if(playerOrdersStatus[player.name])
            {
                // ... it executes an order
                /* TODO: replace with ordersList. Also, check that once an order is executed, it is removed from the
                list of a player's orders. */
                player.orders[0]->execute();

                if(player.orders.empty())
                    playerOrdersStatus[player.name] = false;

                // If it has no more orders...
                if(!playerOrdersStatus[player.name])
                {
                    // ... we add it to the number of players that are done.
                    amountOfPlayersDone++;
                }
            }
        }
    }

    // Every order has been executed.
}