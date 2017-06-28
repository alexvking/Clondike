//
//  Deck.cpp
//  Clondike
//
//  Created by Alex King on 6/27/17.
//  Copyright © 2017 Alex King. All rights reserved.
//

#include <random>
#include "Deck.hpp"

Deck::Deck()
{
    for (int r = 0; r < NUM_RANKS; r++) {
        for (int s = 0; s < NUM_SUITS; s++) {
            cardsList.push_back(Card(Rank(r), Suit(s)));
        }
    }
}

void Deck::flip()
{
    std::reverse(cardsList.begin(), cardsList.end());
}

void Deck::shuffle()
{
    std::random_device rd;
    std::mt19937 g(rd());
    
    std::shuffle(cardsList.begin(), cardsList.end(), g);
}

