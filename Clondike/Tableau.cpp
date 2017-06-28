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

bool Tableau::isEmpty()
{
    return cardsList.empty();
}

bool Tableau::isFull()
{
    return cardsList.back().rank == RANK_A;
}

bool Tableau::addCard(Card c)
{
    if (this->isEmpty()) {
        if (c.rank == RANK_K) {
            cardsList.push_back(c);
            return true;
        }
    // if not empty, check that the card is one smaller, and that the suit color
    // is different. Red is even and black is odd, so we expect a valid sum to
    // be odd
    } else if ((cardsList.back().rank == c.rank + 1) and
               ((cardsList.back().rank + c.rank) % 2 == 1)) {
        cardsList.push_back(c);
        return true;
    }
    return false;
}

void Tableau::deal(Card c)
{
    cardsList.push_back(c);
}

Card Tableau::cardAt(int i)
{
    return cardsList.at(i);
}

int Tableau::size()
{
    return cardsList.size();
}
