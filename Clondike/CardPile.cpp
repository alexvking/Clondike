//
//  CardPile.cpp
//  Clondike
//
//  Created by Alex King on 6/27/17.
//  Copyright © 2017 Alex King. All rights reserved.
//

#include "CardPile.hpp"

bool CardPile::isEmpty()
{
    return cardsList.empty();
}

bool CardPile::addCard(Card c)
{
    cardsList.push_back(c);
    return true;
}

Card CardPile::cardAt(int i)
{
    return cardsList.at(i);
}

int CardPile::size()
{
    return cardsList.size();
}

bool CardPile::canPlaceCard(Card c)
{
    return false;
}

// Removes card at top of pile and returns it
Card CardPile::dealFromTop()
{
    Card c = cardsList.back();
    cardsList.pop_back();
    return c;
}

Card CardPile::cardAtTop()
{
    return cardsList.back();
}

int CardPile::getNumCardsFaceUp()
{
    return numCardsFaceUp;
}

void CardPile::setNumCardsFaceUp(int cardsFaceUp)
{
    numCardsFaceUp = cardsFaceUp;
}
