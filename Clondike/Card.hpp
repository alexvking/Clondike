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
    Card(Rank r, Suit s);
    friend std::ostream &operator<<(std::ostream &os, Card const &c);

    Rank rank;
    Suit suit;
};

#endif /* Card_hpp */
