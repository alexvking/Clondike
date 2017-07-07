//
//  Card.cpp
//  Clondike
//
//  Created by Alex King on 6/30/17.
//  Copyright © 2017 Alex King. All rights reserved.
//

#include "Card.hpp"

Card::Card()
{
    this->rank = RANK_2;
    this->suit = HEART;
}

Card::Card(Rank r, Suit s)
{
   this->rank = r;
   this->suit = s;
}
