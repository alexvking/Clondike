//
//  Card.hpp
//  Clondike
//
//  Created by Alex King on 6/27/17.
//  Copyright © 2017 Alex King. All rights reserved.
//

#ifndef Card_hpp
#define Card_hpp

#include <string>

enum Rank {
    RANK_A, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_9,
    RANK_10, RANK_J, RANK_Q, RANK_K, NUM_RANKS
};

/*
 Red is even, black is odd -- makes for easy math for legal card placement
*/
enum Suit {
    HEART, CLUB, DIAMOND, SPADE, NUM_SUITS
};

static std::string rankNames = "A23456789TJQK";
static std::string suitNames = "HCDS";

class Card {
public:
    Card();
    Card(Rank r, Suit s);

    Rank rank;
    Suit suit;
};

#endif /* Card_hpp */
