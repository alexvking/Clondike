//
//  DrawPile.cpp
//  Clondike
//
//  Created by Alex King on 6/27/17.
//  Copyright © 2017 Alex King. All rights reserved.
//

#include "DrawPile.hpp"

bool DrawPile::isEmpty()
{
    return cardsList.empty();
}

bool DrawPile::addCard(Card c)
{
    cardsList.push_back(c);
    return true;
}

int DrawPile::size()
{
    return cardsList.size();
}

Card DrawPile::cardAt(int i)
{
    return cardsList.at(i);
}
