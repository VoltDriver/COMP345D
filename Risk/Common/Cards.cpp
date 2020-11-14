#include <string>
#include <map>
#include <algorithm>
#include <stdexcept>
#include <list>
#include <random>
#include "Cards.h"
#include "Player.h"

// Card

std::string Card::toString() const {

    // Mapping the type enum values to textual names.
    std::map<CardType,std::string> cardTypeMap;
    cardTypeMap[Bomb] = "Bomb";
    cardTypeMap[Reinforcement] = "Reinforcement";
    cardTypeMap[Blockade] = "Blockade";
    cardTypeMap[Airlift] = "Airlift";
    cardTypeMap[Diplomacy] = "Diplomacy";

    // Returning the name of the type associated with this card.
    return cardTypeMap[*this->type];
}

void Card::play(Player* player, Deck* deck, Map* map) {
    // Saving the type temporarily.
    CardType cardType = *this->type;

    // Creating an order ID provider
    ID id = ID();

    // We use Mt19937 and random_device, which seeds the random generator with some random data from the system.
    // There's other ways to do it, but this is efficient and does not require seeding with Time.
    std::random_device randomDevice;
    std::mt19937 mt(randomDevice());

    switch(*this->type)
    {
        case Bomb:
        {
            // Bomb

            // List the territories the player can choose
            cout << "In which territory would you like to launch your bomb?"<< endl;
            std::map<int, Territory*> territoryToNumberMap = std::map<int, Territory*>();
            int counter = 0;
            for(Territory* t : player->to_attack())
            {
                territoryToNumberMap[counter] = t;
                counter++;
            }

            // Generate a random input
            std::uniform_int_distribution<int> distribution(0,territoryToNumberMap.size() - 1);
            int territoryChoice = distribution(mt);

            // TODO: Create the order properly... And implement a constructor that makes them automatically.
            auto* bombOrder = new class::Bomb(id.setID());
            player->addOrder(bombOrder);

            cout << "Bomb order issued." << endl;
            break;
        }
        case Reinforcement:
        {
            // TODO: Check that the amount of armies given is fine, and if we need an ORDER class for it.
            player->reinforcementPool += 15;
            cout << "Reinforcements Added.";
            break;
        }
        case Blockade:
        {
            // Blockade

            std::map<int, Territory*> territoryToNumberMap = std::map<int, Territory*>();
            int counter = 0;
            for(Territory* t : player->to_defend())
            {
                territoryToNumberMap[counter] = t;
                counter++;
            }

            // Generate a random input
            std::uniform_int_distribution<int> distribution(0,territoryToNumberMap.size() - 1);

            int territoryChoice = distribution(mt);

            // TODO: Create the order properly... And implement a constructor that makes them automatically.
            auto* blockadeOrder = new class::Blockade(id.setID());
            player->addOrder(blockadeOrder);

            cout << "Blockade order issued." << endl;
            break;
            break;
        }
        case Airlift:
        {
            // Choosing a starting point
            std::map<int, Territory*> sourceTerritoryToNumberMap = std::map<int, Territory*>();
            int counter = 0;
            for(Territory* t : player->to_defend())
            {
                sourceTerritoryToNumberMap[counter] = t;

                cout << counter << ": " << t->get_name() << " (" << t->get_armies() << " troops)" << endl;
                counter++;
            }

            // Generate a random input
            std::uniform_int_distribution<int> distribution(0,sourceTerritoryToNumberMap.size() - 1);

            int sourceTerritoryChoice = distribution(mt);

            // Choosing randomly a number of troops to move
            std::uniform_int_distribution<int> distributionTroops(0,player->reinforcementPool);

            int troopNumber = distributionTroops(mt);

            // Choose a territory for the player to advance to.
            std::map<int, Territory*> destinationTerritoryToNumberMap = std::map<int, Territory*>();
            int counter2 = 0;

            // Advancing to any territory
            for(Territory* t : map->territories)
            {
                destinationTerritoryToNumberMap[counter2] = t;
                counter2++;
            }

            // Choosing randomly a territory to move to
            std::uniform_int_distribution<int> distributionDestination(0,destinationTerritoryToNumberMap.size() - 1);

            int destinationTerritoryChoice = distributionDestination(mt);

            // TODO: Create the order properly... And implement a constructor that makes them automatically.
            auto* airliftOrder = new class::Airlift(id.setID());
            player->addOrder(airliftOrder);

            cout << "Airlift order issued." << endl;
            break;
        }
        case Diplomacy:
        {
            // TODO: Implement properly.
            break;
        }

        default:
            throw exception("Invalid card type to play.");
            break;
    }

    // Adding this card back into the deck.
    deck->addCard(cardType);

    // Removing the card from the player's hand.
    player->hand->removeCard(cardType);
}

void Card::playHuman(Player* player, Deck* deck, Map* map) {
    // Saving the type temporarily.
    CardType cardType = *this->type;

    // Creating an order ID provider
    ID id = ID();

    switch(*this->type)
    {
        case Bomb:
        {
            // Bomb

            // List the territories the player can choose
            cout << "In which territory would you like to launch your bomb?"<< endl;
            std::map<int, Territory*> territoryToNumberMap = std::map<int, Territory*>();
            int counter = 0;
            for(Territory* t : player->to_attack())
            {
                territoryToNumberMap[counter] = t;

                cout << counter << ": " << t->get_name() << " (" << t->get_armies() << " troops)" << endl;
                counter++;
            }

            // Read input and validate it.
            int territoryChoice = -1;
            while(territoryChoice<0 || territoryChoice > player->to_attack().size())
                cin >> territoryChoice;

            // TODO: Create the order properly... And implement a constructor that makes them automatically.
            auto* bombOrder = new class::Bomb(id.setID(), territoryToNumberMap.at(territoryChoice), player);
            player->addOrder(bombOrder);

            cout << "Bomb order issued." << endl;
            break;
        }
        case Reinforcement:
        {
            // TODO: Check that the amount of armies given is fine, and if we need an ORDER class for it.
            player->reinforcementPool += 15;
            cout << "Reinforcements Added.";
            break;
        }
        case Blockade:
        {
            // Blockade

            // List the territories the player can choose
            cout << "In which territory would you like to set up your blockade?"<< endl;
            std::map<int, Territory*> territoryToNumberMap = std::map<int, Territory*>();
            int counter = 0;
            for(Territory* t : player->to_defend())
            {
                territoryToNumberMap[counter] = t;

                cout << counter << ": " << t->get_name() << " (" << t->get_armies() << " troops)" << endl;
                counter++;
            }

            // Read input and validate it.
            int territoryChoice = -1;
            while(territoryChoice<0 || territoryChoice > player->to_attack().size())
                cin >> territoryChoice;

            // TODO: Create the order properly... And implement a constructor that makes them automatically.
            auto* blockadeOrder = new class::Blockade(id.setID(), territoryToNumberMap.at(territoryChoice), player);
            player->addOrder(blockadeOrder);

            cout << "Blockade order issued." << endl;
            break;
            break;
        }
        case Airlift:
        {
            // List the territories the player can choose as starting point
            cout << "From which territory would you like to select troops from?"<< endl;
            std::map<int, Territory*> sourceTerritoryToNumberMap = std::map<int, Territory*>();
            int counter = 0;
            for(Territory* t : player->to_defend())
            {
                sourceTerritoryToNumberMap[counter] = t;

                cout << counter << ": " << t->get_name() << " (" << t->get_armies() << " troops)" << endl;
                counter++;
            }

            // Read input and validate it.
            int sourceTerritoryChoice = -1;
            while(sourceTerritoryChoice<0 || sourceTerritoryChoice > player->to_defend().size())
                cin >> sourceTerritoryChoice;

            cout << "How many troops would you like to move? (" << sourceTerritoryToNumberMap[sourceTerritoryChoice]->get_armies() << " remaining in your territory.)" << endl;

            // Read input and validate it.
            int troopNumber = -1;
            while(troopNumber<0 || troopNumber > player->reinforcementPool)
                cin >> troopNumber;

            // List the territories the player can choose to advance to
            cout << "To which territory would you like to advance your troops to?"<< endl;
            std::map<int, Territory*> destinationTerritoryToNumberMap = std::map<int, Territory*>();
            int counter2 = 0;

            cout << "Territories to attack: " << endl;
            // Advancing to any territory
            for(Territory* t : map->territories)
            {
                if(t->get_player() != player)
                {
                    destinationTerritoryToNumberMap[counter2] = t;
                    cout << counter2 << ": " << t->get_name() << " (" << t->get_armies() << " troops)" << endl;
                    counter2++;
                }
            }

            cout << "Territories to defend: " << endl;

            for(Territory* t : player->to_defend())
            {
                destinationTerritoryToNumberMap[counter2] = t;
                cout << counter2 << ": " << t->get_name() << " (" << t->get_armies() << " troops)" << endl;
                counter2++;
            }

            // Read input and validate it.
            int destinationTerritoryChoice = -1;
            while(destinationTerritoryChoice<0 || destinationTerritoryChoice > (player->to_attack().size() + player->to_defend().size()) )
                cin >> destinationTerritoryChoice;

            // TODO: Create the order properly... And implement a constructor that makes them automatically.
            auto* airliftOrder = new class::Airlift(id.setID(), troopNumber, sourceTerritoryToNumberMap.at(sourceTerritoryChoice), destinationTerritoryToNumberMap.at(destinationTerritoryChoice), player);
            player->addOrder(airliftOrder);

            cout << "Airlift order issued." << endl;
            break;
        }
        case Diplomacy:
        {
            // TODO: Implement properly.
            break;
        }

        default:
            throw exception("Invalid card type to play.");
            break;
    }

    // Adding this card back into the deck.
    deck->addCard(cardType);

    // Removing the card from the player's hand.
    player->hand->removeCard(cardType);
}

Card::Card() {
    // By default, creating a card gives it the type Bomb.
    type = new CardType(Bomb);
}

Card::Card(const Card &card) {
    CardType* newType = new CardType(*card.type);
    type = newType;
}

Card::Card(CardType type) : type(new CardType(type)) {
}

Card& Card::operator=(const Card &card) {
    // Cleaning up
    delete this->type;

    // Assigning the new type.
    this->type = new CardType(*card.type);
    return *this;
}

std::ostream &operator<<(std::ostream &out, const Card& card) {
    // Outputting the card in string format using its relevant method.
    return out << card.toString();
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

Card::~Card() {
    // Cleaning up.
    delete this->type;
    this->type = nullptr;
}

// Deck

// Pulls a card from the remaining cards in the deck.
void Deck::draw(Hand* hand) {

    // Generating a random index that is in the list.
    // We use Mt19937 and random_device, which seeds the random generator with some random data from the system.
    // There's other ways to do it, but this is efficient and does not require seeding with Time.
    std::random_device randomDevice;
    std::mt19937 mt(randomDevice());
    std::uniform_int_distribution<int> distribution(0,this->cards->size() - 1);
    int randomIndex = distribution(mt);

    // Drawing the card at the index generated.
    auto iterator = std::next(this->cards->begin(), randomIndex);
    // Copying the card to the heap, so that we have a deep copy.
    Card* pulled = new Card(*iterator);

    // Adding the card we pulled to the hand
    hand->addCard(*pulled);

    // Removing the card from the deck.
    cards->erase(iterator);
}

// Returns the number of cards left in the deck.
int Deck::remainingCards() {
    return cards->size();
}

// Initializes the deck of cards, with a certain amount of each type of card in it.
// This replaces the current deck's content.
void Deck::reset() {
    // Creating a new list.
    std::list<Card>* cards = new std::list<Card>();

    // Pushing a certain amount of each card type into the deck.
    // Currently, we chose 10 of each type.
    for (int i = 0; i < 10; ++i) {
        cards->push_back(*new Card(Bomb));
        cards->push_back(*new Card(Reinforcement));
        cards->push_back(*new Card(Blockade));
        cards->push_back(*new Card(Airlift));
        cards->push_back(*new Card(Diplomacy));
    }

    // Cleaning up.
    delete this->cards;

    // Setting the deck's content to the new list of cards.
    this->cards = cards;
}

// Adds a new card to the deck, with the specified type.
void Deck::addCard(CardType& type) {
    // Creating a new card.
    Card* newCard = new Card(type);
    // Pushing it into the deck.
    this->cards->push_back(*newCard);
}

// Adds the passed card to the deck.
void Deck::addCard(Card &card) {
    this->cards->push_back(card);
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
    this->cards = cards;
}

Deck::Deck(const Deck &deck) {
    // Copies the passed deck's content.
    std::list<Card>* cards = new std::list<Card>(deck.cards->begin(), deck.cards->end());

    // Assign it to this deck.
    this->cards = cards;
}

Deck & Deck::operator=(const Deck &deck) {
    // Copies the passed deck's content.
    std::list<Card>* cards = new std::list<Card>(deck.cards->begin(), deck.cards->end());

    // Clear up our current cards.
    delete this->cards;

    // Assign it to this deck.
    this->cards = cards;

    return *this;
}

std::istream& operator>>(std::istream& in, const Deck& deck)
{
    // Reading card from input.
    Card card;
    in >> card;
    // Pushing card in deck.
    deck.cards->push_back(card);

    // Returning the stream
    return in;
}

std::ostream& operator<<(std::ostream& out, const Deck& deck)
{
    // Creating an iterator
    std::list<Card>::iterator iterator;

    // Iterating through the deck
    for (iterator = deck.cards->begin(); iterator != deck.cards->end(); ++iterator) {
        // Output the card to the stream, using it's textual type.
        out << iterator->toString()<< " ";
    }

    // Returning the stream.
    return out;
}

Deck::~Deck() {
    delete this->cards;
    this->cards = nullptr;
}


// Hand

void Hand::removeCard(CardType& type) {
    // Creating an iterator
    std::list<Card>::iterator iterator;

    bool cardFound = false;

    // Iterating through the hand
    for (iterator = this->cards->begin(); iterator != this->cards->end(); ++iterator) {
        // If we find a card that matches the type, we break the loop.
        if(*iterator->type == type)
        {
            cardFound = true;
            break;
        }
    }

    // Remove the card found.
    if(cardFound)
    {
        this->cards->erase(iterator);
    }
    else
    {
        // If no match is found for the card type passed, then nothing happens.
        // We still want to warn of the error, so we output to console.
        cout << "ERROR: Card not found in player's hand. Could not delete.";
    }
}

Hand::Hand(){
    // Initializes a hand of cards, empty at the start.
    this->cards = new std::list<Card>();
}

Hand::Hand(const Hand &Hand) {
    // Copies the passed hand's content.
    std::list<Card>* cards = new std::list<Card>(Hand.cards->begin(), Hand.cards->end());

    // Assign it to this hand.
    this->cards = cards;
}

Hand & Hand::operator=(const Hand &Hand) {
    // Copies the passed hand's content.
    std::list<Card>* cards = new std::list<Card>(Hand.cards->begin(), Hand.cards->end());

    // Clear up our current cards.
    delete this->cards;

    // Assign it to this hand.
    this->cards = cards;

    return *this;
}

std::istream& operator>>(std::istream& in, const Hand& Hand)
{
    // Reading card from input.
    Card card;
    in >> card;
    // Pushing card in hand.
    Hand.cards->push_back(card);

    // Returning the stream
    return in;
}

std::ostream& operator<<(std::ostream& out, const Hand& Hand)
{
    // Creating an iterator
    std::list<Card>::iterator iterator;

    // Iterating through the hand
    for (iterator = Hand.cards->begin(); iterator != Hand.cards->end(); ++iterator) {
        // Output the card to the stream, using its textual type.
        out << iterator->toString() << " ";
    }

    // Returning the stream.
    return out;
}

Hand::~Hand() {
    // Cleaning up.
    delete this->cards;
    this->cards = nullptr;
}


int Hand::remainingCards() {
    // We use the size property to return the number of elements remaining.
    return this->cards->size();
}

std::string *Hand::listAllCards() {
    // Creating a string to accumulate the cards in.
    auto *result = new std::string("");

    // Creating an iterator
    std::list<Card>::iterator iterator;

    // Iterating through the hand
    for (iterator = this->cards->begin(); iterator != this->cards->end(); ++iterator) {
        // Add the card's type to the result string.
        *result += iterator->toString() + " ";
    }

    return result;
}

void Hand::addCard(CardType& type) {
    // Creating a new card.
    Card* newCard = new Card(type);
    // Pushing it into the hand.
    this->cards->push_back(*newCard);
}


void Hand::addCard(Card &card) {
    // Add the passed card to the hand.
    this->cards->push_back(card);
}