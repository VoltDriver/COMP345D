#ifndef COMP345RISK_CARDS_H
#define COMP345RISK_CARDS_H

#include "Orders.h"
#include <list>
#include <iostream>
#include <cmath>

class Player;

/**
 * Enum containing the different types of card available to be drawn from the deck.
 */
enum CardType{ Bomb, Reinforcement, Blockade, Airlift, Diplomacy};

class Hand;
class Deck;
class Map;

/**
 * Represents a playable card, that can create a special order once played.
 */
class Card {
    public:
        /**
        * The type of the card.
        */
        CardType* type;

        /**
         * Outputs the card into a string format.
         */
        std::string toString() const;

        //         void play(Player* player, Deck* deck, Map* map, const list<Player*>& gamePlayers);
        /**
         * Plays the card, creating a special order in the associated player and adding the card back to the deck.
         * This method is meant to be used by an AI player, and will automatically make any decisions.
         * @param player The player who is playing the card.
         * @param deck The deck to put the card back into.
         */
        void play(Player* player, Deck* deck, Map* map);

        //         void playHuman(Player* player, Deck* deck, Map* map, const list<Player*> gamePlayers);
        /**
         * Plays the card, creating a special order in the associated player and adding the card back to the deck.
         * This method is meant to be used by a human player, and will prompt the user for decisions.
         * @param player The player who is playing the card.
         * @param deck The deck to put the card back into.
         */
        void playHuman(Player* player, Deck* deck, Map* map);

        Card();

        /**
         * Creates a card of a certain specified type.
         * @param type Type of the card to create.
         */
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
        /**
         * Draws a card from the deck, putting it into a hand.
         * @param hand The hand to put the card into.
         */
        void draw(Hand* hand);
        /**
         * Outputs the amount of cards remaining in the deck.
         * @return The amount of cards remaining, in int.
         */
        int remainingCards();
        /**
         * Resets the deck back to its maximum capacity, with a fixed number of each type of card.
         */
        void reset();
        /**
         * Adds a new card of a specific type into the deck.
         * @param type The type of card to add.
         */
        void addCard(CardType& type);
        /**
         * Adds a specified card to the deck.
         * @param card The card to add.
         */
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
        /**
         * Outputs the amount of cards remaining in the hand.
         * @return The amount of cards remaining, in int.
         */
        int remainingCards();
        /**
         * Lists all the cards in the hand, in string format, by outputting their type.
         * @return All the cards currently in the hand.
         */
        std::string* listAllCards();
        /**
         * Adds a new card of a specific type into the deck.
         * @param type The type of card to add.
         */
        void addCard(CardType& type);
        /**
         * Adds a specified card to the deck.
         * @param card The card to add.
         */
        void addCard(Card& card);
        /**
         * Removes a card of the specified type from the hand. The card chosen is the first one found of its type.
         * @param type The type of card to remove.
         */
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
