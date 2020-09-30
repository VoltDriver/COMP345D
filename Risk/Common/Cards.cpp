#include "Cards.h"
#include <string>
#include <map>
#include <algorithm>
#include <stdexcept>

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

        return in;
    }
}


