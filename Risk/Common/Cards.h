#ifndef COMP345RISK_CARDS_H
#define COMP345RISK_CARDS_H

#include "Orders.h"
#include <list>
#include <iostream>

enum CardType{ Bomb, Reinforcement, Blockade, Airlift, Diplomacy};

class Card {
    public:
        CardType* type;
        Order* play();
        Card();
        Card(CardType type);

        // Copy constructor
        Card(const Card& card);

        // Assignment Operator
        Card& operator =(const Card& card);

        // Stream insertion operators
        friend std::istream& operator>>(std::istream& in, const Card& card);
        friend std::ostream& operator<<(std::ostream& out, const Card& card);
};

class Deck {
    public:
        Card* draw();
        int remainingCards();
        void reset();
};

class Hand {
    private:

    public:
        std::list<Card>* listAllCards();
        void addCard();
        void removeCard();
};


#endif //COMP345RISK_CARDS_H
