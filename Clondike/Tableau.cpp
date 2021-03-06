//
//  Tableau.cpp
//  Clondike
//
//  Created by Alex King on 6/27/17.
//  Copyright © 2017 Alex King. All rights reserved.
//

#include "Tableau.hpp"

Tableau::Tableau()
{
    numCardsFaceUp = 1;
}

bool Tableau::isFull()
{
    return cardsList.back().rank == RANK_A;
}

bool Tableau::canPlaceCard(Card c)
{
    if (this->isEmpty()) {
        if (c.rank == RANK_K) {
            return true;
        }
    // if not empty, check that the card is one smaller, and that the suit color
    // is different. Red is even and black is odd, so we expect a valid sum to
    // be odd
    } else if ((cardsList.back().rank == c.rank + 1) and
               ((cardAtTop().suit + c.suit) % 2 == 1)) {
        return true;
    }
    return false;
}

int Tableau::getNumCardsFaceUp()
{
    return numCardsFaceUp;
}
void Tableau::setNumCardsFaceUp(int cardsFaceUp)
{
    numCardsFaceUp = cardsFaceUp;
}
