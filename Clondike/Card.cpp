//
//  Card.cpp
//  Clondike
//
//  Created by Alex King on 6/27/17.
//  Copyright © 2017 Alex King. All rights reserved.
//

#include "Card.hpp"

const char* suitNames = "HCDS";
const char* rankNames = "A23456789TJQK";

Card::Card(Suit s, Rank r)
{
    this->suit = s;
    this->rank = r;
}
