//
//  Deck.hpp
//  Clondike
//
//  Created by Alex King on 6/27/17.
//  Copyright © 2017 Alex King. All rights reserved.
//

#ifndef Deck_hpp
#define Deck_hpp

#include <stdio.h>
#include "CardPile.hpp"
#include <vector>

class Deck: public CardPile {
public:
    Deck();
    void shuffle();
    void flip();
};

#endif /* Deck_hpp */
