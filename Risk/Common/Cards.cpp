#include "Cards.h"
#include <string>
#include <map>
#include <algorithm>
#include <stdexcept>
#include <list>
#include <random>

// Card

std::string Card::toString() {
    // Mapping the type enum values to textual names.
    std::map<CardType,std::string> cardTypeMap;
    cardTypeMap[Bomb] = "Bomb";
    cardTypeMap[Reinforcement] = "Reinforcement";
    cardTypeMap[Blockade] = "Blockade";
    cardTypeMap[Airlift] = "Airlift";
    cardTypeMap[Diplomacy] = "Diplomacy";

    return cardTypeMap[*this->type];
}

Order *Card::play() {
    // TODO: Implement this properly.
    return new Order();
}

Card::Card() {
    // TODO: Check what default type we want.
    type = new CardType(Bomb);
}

Card::Card(const Card &card) {
    CardType* newType = new CardType(*card.type);
    type = newType;
}

Card::Card(CardType type) : type(new CardType(type)) {
}

Card& Card::operator=(const Card &card) {
    delete this->type;
    this->type = new CardType(*card.type);
    return *this;
}

std::ostream &operator<<(std::ostream &out, const Card& card) {
    return out << *card.type;
}

std::istream &operator>>(std::istream &in, const Card &card) {
    std::string input;
    in >> input;

    // Verifying if what the stream gave us is a number.
    bool isNumber = !input.empty()
                    && std::all_of(input.begin(), input.end(), ::isdigit);

    // If the stream gave us a number...
    if(isNumber)
    {
        // Cleaning up our pointer.
        delete card.type;
        // Converting the string to an int, and then matching that int with the proper enum value.
        *card.type = static_cast<CardType>(std::stoi(input));
    }
    else
    {
        // Mapping the textual name of a card to its proper enum value.
        std::map<std::string,CardType> cardTypeMap;
        cardTypeMap["Bomb"] = Bomb;
        cardTypeMap["Reinforcement"] = Reinforcement;
        cardTypeMap["Blockade"] = Blockade;
        cardTypeMap["Airlift"] = Airlift;
        cardTypeMap["Diplomacy"] = Diplomacy;

        // Checking if the key we've been given exists in our map,
        // i.e. if the value given to us by the stream is valid.
        if ( cardTypeMap.find(input) == cardTypeMap.end() )
        {
            // The value was invalid.
            throw std::invalid_argument("The card type provided does not exists.");
        }
        else
        {
            // It's valid.

            // Cleaning up our pointer.
            delete card.type;

            *card.type = cardTypeMap[input];
        }
    }
    return in;
}

// Deck

// Pulls a card from the remaining cards in the deck.
Card * Deck::draw() {

    // Generating a random index that is in the list.
    // We use Mt19937 and random_device, which seeds the random generator with some random data from the system.
    // There's other ways to do it, but this is efficient and does not require seeding with Time.
    std::random_device randomDevice;
    std::mt19937 mt(randomDevice());
    std::uniform_int_distribution<int> distribution(0,this->Cards->size());
    int randomIndex = distribution(mt);

    // Drawing the card at the index generated.
    auto iterator = std::next(this->Cards->begin(), randomIndex);
    // Copying the card to the heap, so that we have a deep copy.
    Card* pulled = new Card(*iterator);

    // Removing the card from the deck.
    Cards->erase(iterator);

    // Returning the card we pulled.
    return pulled;
}

// Returns the number of cards left in the deck.
int Deck::remainingCards() {
    return Cards->size();
}

// Initializes the deck of cards, with a certain amount of each type of card in it.
// This replaces the current deck's content.
void Deck::reset() {
    // Creating a new list.
    std::list<Card>* cards = new std::list<Card>();

    // Pushing a certain amount of each card type into the deck.
    for (int i = 0; i < 10; ++i) {
        cards->push_back(*new Card(Bomb));
        cards->push_back(*new Card(Reinforcement));
        cards->push_back(*new Card(Blockade));
        cards->push_back(*new Card(Airlift));
        cards->push_back(*new Card(Diplomacy));
    }

    delete this->Cards;

    // Setting the deck's content to the new list of cards.
    this->Cards = cards;
}

// Initializes a deck of cards, that starts with a certain amount of each type of card in it.
Deck::Deck(){
    // Creating a new list.
    std::list<Card>* cards = new std::list<Card>();

    // Pushing a certain amount of each card type into the deck.
    for (int i = 0; i < 10; ++i) {
        cards->push_back(*new Card(Bomb));
        cards->push_back(*new Card(Reinforcement));
        cards->push_back(*new Card(Blockade));
        cards->push_back(*new Card(Airlift));
        cards->push_back(*new Card(Diplomacy));
    }

    // Setting the deck's content to the new list of cards.
    this->Cards = cards;
}

Deck::Deck(const Deck &deck) {
    // Copies the passed deck's content.
    std::list<Card>* cards = new std::list<Card>(deck.Cards->begin(), deck.Cards->end());

    // Assign it to this deck.
    this->Cards = cards;
}

Deck & Deck::operator=(const Deck &deck) {
    // Copies the passed deck's content.
    std::list<Card>* cards = new std::list<Card>(deck.Cards->begin(), deck.Cards->end());

    // Clear up our current cards.
    delete this->Cards;

    // Assign it to this deck.
    this->Cards = cards;

    return *this;
}

std::istream& operator>>(std::istream& in, const Deck& deck)
{
    // Reading card from input.
    Card card;
    in >> card;
    // Pushing card in deck.
    deck.Cards->push_back(card);

    // Returning the stream
    return in;
}

std::ostream& operator<<(std::ostream& out, const Deck& deck)
{
    // Creating an iterator
    std::list<Card>::iterator iterator;

    // Iterating through the deck
    for (iterator = deck.Cards->begin(); iterator != deck.Cards->end(); ++iterator) {
        // Output the card to the stream, using it's textual type.
        out << iterator->toString()<< " ";
    }

    // Returning the stream.
    return out;
}

// Hand

// Removes a card from hand that matches the card type passed.
// If no match is found for the card type passed, then nothing happens.
void Hand::removeCard(CardType& type) {
    // Creating an iterator
    std::list<Card>::iterator iterator;

    bool cardFound = false;

    // Iterating through the hand
    for (iterator = this->Cards->begin(); iterator != this->Cards->end(); ++iterator) {
        // If we find a card that matches the type, we break the loop.
        if(*iterator->type == type)
        {
            cardFound = true;
            break;
        }
    }

    // Remove the card found.
    if(cardFound)
        this->Cards->erase(iterator);
}

// Initializes a hand of cards, empty at the start.
Hand::Hand(){
    this->Cards = new std::list<Card>();
}

Hand::Hand(const Hand &Hand) {
    // Copies the passed hand's content.
    std::list<Card>* cards = new std::list<Card>(Hand.Cards->begin(), Hand.Cards->end());

    // Assign it to this hand.
    this->Cards = cards;
}

Hand & Hand::operator=(const Hand &Hand) {
    // Copies the passed hand's content.
    std::list<Card>* cards = new std::list<Card>(Hand.Cards->begin(), Hand.Cards->end());

    // Clear up our current cards.
    delete this->Cards;

    // Assign it to this hand.
    this->Cards = cards;

    return *this;
}

std::istream& operator>>(std::istream& in, const Hand& Hand)
{
    // Reading card from input.
    Card card;
    in >> card;
    // Pushing card in hand.
    Hand.Cards->push_back(card);

    // Returning the stream
    return in;
}

std::ostream& operator<<(std::ostream& out, const Hand& Hand)
{
    // Creating an iterator
    std::list<Card>::iterator iterator;

    // Iterating through the hand
    for (iterator = Hand.Cards->begin(); iterator != Hand.Cards->end(); ++iterator) {
        // Output the card to the stream, using its textual type.
        out << iterator->toString() << " ";
    }

    // Returning the stream.
    return out;
}


int Hand::remainingCards() {
    return this->Cards->size();
}


// Outputs all cards in the hand into a string, naming their type.
std::string *Hand::listAllCards() {
    // Creating a string to accumulate the cards in.
    auto *result = new std::string("");

    // Creating an iterator
    std::list<Card>::iterator iterator;

    // Iterating through the hand
    for (iterator = this->Cards->begin(); iterator != this->Cards->end(); ++iterator) {
        // Add the card's type to the result string.
        *result += iterator->toString() + " ";
    }

    return result;
}

// Adds a new card to the hand, with the specified type.
void Hand::addCard(CardType& type) {
    // Creating a new card.
    Card* newCard = new Card(type);
    // Pushing it into the hand.
    this->Cards->push_back(*newCard);
}

// Adds the passed card to the hand.
void Hand::addCard(Card &card) {
    this->Cards->push_back(card);
}