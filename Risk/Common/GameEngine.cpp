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
        issueOrdersPhase();

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
                playerTurns[player.name] = player.issueOrder();

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

void GameEngine::startupPhase(){
    list<Player>::iterator it;
    vector<int> ordersOfPlay;
    switch(players.size()){
        case 2:
            cout << "40 initial armies for every player!" << endl;
            ordersOfPlay = {1,2};
            for(it = players.begin(); it != players.end(); ++it){
                it->reinforcementPool = 40;
                int random = rand() % (ordersOfPlay.size()-1);
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
                int random = rand() % (ordersOfPlay.size()-1);
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
                int random = rand() % (ordersOfPlay.size()-1);
                it->orderOfPlay = ordersOfPlay[random];
                ordersOfPlay.erase(ordersOfPlay.begin() + random);
                ordersOfPlay.shrink_to_fit();
            }
            break;
        case 5:
            cout << "25 initial armies for every player!" << endl;
            ordersOfPlay = {1,2,3,4,5};
            for(it = players.begin(); it != players.end(); ++it){
                it->reinforcementPool = 35;
                int random = rand() % (ordersOfPlay.size()-1);
                it->orderOfPlay = ordersOfPlay[random];
                ordersOfPlay.erase(ordersOfPlay.begin() + random);
                ordersOfPlay.shrink_to_fit();
            }
            break;
    }

    /*
    for(auto territory: map.territories){
        int random = rand() % (players.size()-1);
        advance(it, random);
        it->territories.push_back(territory);
    }
    */
    vector<Territory*> copyOfMapTerritories = map.territories;
    while(copyOfMapTerritories.size() != 0){
        for(it = players.begin(); it != players.end(); ++it){
            int random = rand() % (copyOfMapTerritories.size()-1);
            it->territories.push_back(copyOfMapTerritories[random]);
            copyOfMapTerritories.erase(copyOfMapTerritories.begin() + random);
            copyOfMapTerritories.shrink_to_fit();
        }
    }


}



