//
//  Card.cpp
//  Clondike
//
//  Created by Alex King on 6/30/17.
//  Copyright © 2017 Alex King. All rights reserved.
//

#include "Card.hpp"
#include <stdio.h>
#include <iostream>

Card::Card(Rank r, Suit s)
{
   this->rank = r;
   this->suit = s;
}

std::ostream &operator<<(std::ostream &os, Card const &c)
{
    switch (c.suit) {
        case HEART:
            os << (COLOR ? "\033[32;41m" : "") << rankNames[c.rank] 
               << suitNames[c.suit] << (COLOR ? "\033[0m" : "");
            break;
        case SPADE:
            os << (COLOR ? "\033[36;40m" : "") << rankNames[c.rank] 
               << suitNames[c.suit] << (COLOR ? "\033[0m" : "");
            break;
        case CLUB:
            os << (COLOR ? "\033[33;40m" : "") << rankNames[c.rank] 
               << suitNames[c.suit] << (COLOR ? "\033[0m" : "");
            break;
        case DIAMOND:
            os << (COLOR ? "\033[37;41m" : "") << rankNames[c.rank] 
               << suitNames[c.suit] << (COLOR ? "\033[0m" : "");
            break;
        default:
            break;
    }
    return os;
}