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

    while(!gameOver)
    {
        // Reinforcement Phase
        reinforcementPhase();

        // Issuing Orders Phase

        // Orders Execution Phase

        // Checking if the game is over
        for(Player player : players)
        {
            if(player.territories.size() == map.get_territories().size())
                gameOver = true;
        }
    }
}

void GameEngine::reinforcementPhase() {
    for(const Player& player : players)
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
        //TODO: Implement this.
    }
}

void GameEngine::issueOrdersPhase() {

}

Order GameEngine::queryOrderFromUser() {

}