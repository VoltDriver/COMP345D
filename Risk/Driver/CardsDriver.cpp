#include <iostream>
#include "Common/Cards.h"
#include "Common/Player.h"

int main() {
     // Creating a dummy player
    Player* player = new Player();

    std::cout << "Showing the current orders of our player:" << std::endl;
    // Outputting the orders that the player has.
    cout << "\nPrinting player object" << endl;
    cout << *player;

    list<Player*> players = list<Player*>();
    players.push_back(player);

    // Testing the Card class
    std::cout << "***** Test Card class *****" << std::endl;

    std::cout << "Testing output to console..." << std::endl;
    Card* card = new Card();
    Card* card2 = new Card(CardType::Diplomacy);

    std::cout << *card << std::endl;
    std::cout << *card2 << std::endl;

    std::cout << "***** Test Deck and Hand classes *****" << std::endl;

    // Making a deck.
    Deck* newDeck = new Deck();

    std::cout << "There are " << newDeck->remainingCards() << " cards in the deck." << std::endl;

    newDeck->reset();

    std::cout << "There are " << newDeck->remainingCards() << " cards in the deck, after reset." << std::endl;

    std::cout << "The cards are... " << *newDeck << std::endl;

    // Making a hand.
    Hand* newHand = new Hand();
    delete player->hand;
    player->hand = newHand;


    std::cout << "There are " << newHand->remainingCards() << " cards in the hand." << std::endl;

    // Drawing 10 cards from the deck.
    for (int i = 0; i < 10; ++i) {
        std::cout << "Drawing a card."<< std::endl;
        newDeck->draw(newHand);
    }

    std::cout << "There are " << newHand->remainingCards() << " cards in the hand." << std::endl;
    std::cout << "The cards are... " << *newHand->listAllCards() << std::endl;

    std::cout << "There are " << newDeck->remainingCards() << " cards in the deck." << std::endl;


    int amountOfCards = newHand->remainingCards();

    for (int i = 0; i < amountOfCards; ++i) {
        Card currentCard = newHand->cards->front();

        std::cout << "Playing a card: "<< currentCard.toString() << std::endl;
        currentCard.play(player, newDeck, nullptr, players);
        std::cout << "There are " << newHand->remainingCards() << " cards in the hand." << std::endl;
        std::cout << "The cards are... " << *newHand->listAllCards() << std::endl;
    }

    std::cout << "There are " << newDeck->remainingCards() << " cards in the deck." << std::endl;

    // Outputting the orders that the player has, which should now have orders.
    cout << "\nPrinting player object" << endl;
    cout << *player;

    // Cleaning up
    delete player;
    delete card;
    delete card2;
    delete newDeck;

    return 0;
}
