#include <iostream>
#include "Common/Cards.h"

int main() {
    std::cout << "Test Cards executable" << std::endl;

    Card* card = new Card();
    Card* card2 = new Card(CardType::Bomb);

    std::cout << *card  << "|"<< *card2;

    return 0;
}
