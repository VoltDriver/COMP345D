#ifndef COMP345RISK_CARDS_H
#define COMP345RISK_CARDS_H

#include "Orders.h"
#include <list>
#include <iostream>

enum CardType{ Bomb, Reinforcement, Blockade, Airlift, Diplomacy};

class Hand;
class Deck;

class Card {
    public:
        CardType* type;

        std::string toString() const;

        void play(Hand* hand, Deck* deck);
        Card();
        Card(CardType type);

        // Copy constructor
        Card(const Card& card);

        // Assignment Operator
        Card& operator =(const Card& card);

        // Stream insertion operators
        friend std::istream& operator>>(std::istream& in, const Card& card);
        friend std::ostream& operator<<(std::ostream& out, const Card& card);

        // Destructor
        ~Card();
};

class Deck {
    private:
        std::list<Card>* cards;

    public:
        void draw(Hand* hand);
        int remainingCards();
        void reset();
        void addCard(CardType& type);
        void addCard(Card& card);

        Deck();

        // Copy constructor
        Deck(const Deck& deck);

        // Assignment Operator
        Deck& operator =(const Deck& deck);

        // Stream insertion operators
        friend std::istream& operator>>(std::istream& in, const Deck& deck);
        friend std::ostream& operator<<(std::ostream& out, const Deck& deck);

        // Destructor
        ~Deck();
};

class Hand {
    public:
        std::list<Card>* cards;
        int remainingCards();
        std::string* listAllCards();
        void addCard(CardType& type);
        void addCard(Card& card);
        void removeCard(CardType& type);

        Hand();

        // Copy constructor
        Hand(const Hand& hand);

        // Assignment Operator
        Hand& operator =(const Hand& hand);

        // Stream insertion operators
        friend std::istream& operator>>(std::istream& in, const Hand& hand);
        friend std::ostream& operator<<(std::ostream& out, const Hand& hand);

        // Destructor
        ~Hand();
};


#endif //COMP345RISK_CARDS_H
