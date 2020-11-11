#pragma once

#include <vector>

class Player;

class Deck;

class Map;

class GameEngine {
public:
    // TODO: STUB METHOD. To be implemented.
    void issueOrdersPhase();

    // TODO: STUB METHOD. To be implemented.
    void mainGameLoop();

    // TODO: STUB METHOD. To be implemented.
    void startupPhase();

    // TODO: STUB METHOD. To be implemented.
    void gameStart();

    // TODO: STUB METHOD. To be implemented.
    void reinforcementPhase();

    // TODO: STUB METHOD. To be implemented.
    void issuingOrdersPhase();

    // TODO: STUB METHOD. To be implemented.
    void executeOrdersPhase();

private:
    bool phase_observer_flag;
    bool stat_observer_flag;
    std::vector<Player *> players;
    Map *map;
    Deck *deck;
};