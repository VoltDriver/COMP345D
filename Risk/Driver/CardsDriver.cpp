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

    std::cout << "Drawing a card."<< std::endl;
    newHand->addCard(*newDeck->draw()->type);
    std::cout << "Drawing a card."<< std::endl;
    newHand->addCard(*newDeck->draw());

    std::cout << "There are " << newHand->remainingCards() << " cards in the hand." << std::endl;
    std::cout << "The cards are... " << *newHand << std::endl;
    std::cout << "The cards are... " << *newHand->listAllCards() << std::endl;

    std::cout << "There are " << newDeck->remainingCards() << " cards in the deck." << std::endl;

    return 0;
}
