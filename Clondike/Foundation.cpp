//
//  Foundation.cpp
//  Clondike
//
//  Created by Alex King on 6/27/17.
//  Copyright © 2017 Alex King. All rights reserved.
//

#include "Foundation.hpp"

bool Foundation::isFull()
{
    return cardsList.size() == 13;
}

bool Foundation::placeCard(Card c)
{
    if (this->isEmpty()) {
        if (c.rank == RANK_A) {
            return true;
        }
    } else if (cardsList.back().suit == c.suit and
               cardsList.back().rank == c.rank - 1) {
        return true;
    }
    return false;
}
