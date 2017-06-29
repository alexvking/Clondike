//
//  Card.hpp
//  Clondike
//
//  Created by Alex King on 6/27/17.
//  Copyright © 2017 Alex King. All rights reserved.
//

#ifndef Card_hpp
#define Card_hpp

#include <stdio.h>
#include <iostream>

#define COLOR true

using namespace std;

enum Rank {
    RANK_A, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_9,
    RANK_10, RANK_J, RANK_Q, RANK_K, NUM_RANKS
};

enum Suit {
    HEART, CLUB, DIAMOND, SPADE, NUM_SUITS // red is even, black is odd
};

static string rankNames = "A23456789TJQK";
static string suitNames = "HCDS";

class Card {
public:
    Card(Rank r, Suit s)
    {
        this->rank = r;
        this->suit = s;
    }
    
    Rank rank;
    Suit suit;
    
    friend std::ostream &operator<<(std::ostream &os, Card const &c) {
        switch (c.suit) {
            case HEART:
                cout << (COLOR ? "\033[32;41m" : "") << rankNames[c.rank] << suitNames[c.suit] << (COLOR ? "\033[0m" : "");
                break;
            case SPADE:
                cout << (COLOR ? "\033[36;40m" : "") << rankNames[c.rank] << suitNames[c.suit] << (COLOR ? "\033[0m" : "");
                break;
            case CLUB:
                cout << (COLOR ? "\033[33;40m" : "") << rankNames[c.rank] << suitNames[c.suit] << (COLOR ? "\033[0m" : "");
                break;
            case DIAMOND:
                cout << (COLOR ? "\033[37;41m" : "") << rankNames[c.rank] << suitNames[c.suit] << (COLOR ? "\033[0m" : "");
                break;
            default:
                break;
        }
        return os;
    }

    
};

#endif /* Card_hpp */
