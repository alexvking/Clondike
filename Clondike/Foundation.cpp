//
//  Foundation.cpp
//  Clondike
//
//  Created by Alex King on 6/27/17.
//  Copyright © 2017 Alex King. All rights reserved.
//

#include "Foundation.hpp"

bool Foundation::isEmpty()
{
    return cardsList.empty();
}

bool Foundation::isFull()
{
    return cardsList.size() == 13;
}

bool Foundation::addCard(Card c)
{
    if (this->isEmpty()) {
        if (c.rank == RANK_A) {
            cardsList.push_back(c);
            return true;
        }
    } else if (cardsList.back().suit == c.suit and
               cardsList.back().rank == c.rank - 1) {
        cardsList.push_back(c);
        return true;
    }
    return false;
}

Card Foundation::cardAt(int i)
{
    return cardsList.at(i);
}

int Foundation::size()
{
    return cardsList.size();
}