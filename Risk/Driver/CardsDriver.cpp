#include <iostream>
#include "Common/Cards.h"

int main() {
    std::cout << "Test Cards class" << std::endl;

    Card* card = new Card();
    Card* card2 = new Card(CardType::Bomb);

    std::cout << *card  << "|"<< *card2 << std::endl;

    std::cout << "Test Deck Class, and making a deck." << std::endl;

    Deck* newDeck = new Deck();

    std::cout << "There are " << newDeck->remainingCards() << " cards in the deck." << std::endl;

    newDeck->reset();

    std::cout << "There are " << newDeck->remainingCards() << " cards in the deck, after reset." << std::endl;

    std::cout << "The cards are... " << *newDeck << std::endl;

    Hand* newHand = new Hand();

    std::cout << "There are " << newHand->remainingCards() << " cards in the hand." << std::endl;

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
        currentCard.play(newHand, newDeck);
        std::cout << "There are " << newHand->remainingCards() << " cards in the hand." << std::endl;
        std::cout << "The cards are... " << *newHand->listAllCards() << std::endl;
    }

    std::cout << "There are " << newDeck->remainingCards() << " cards in the deck." << std::endl;

    return 0;
}
