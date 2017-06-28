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
    

    friend std::ostream &operator<<(std::ostream &os, Deck const &d) {
        for (auto ci = d.cardsList.begin(); ci != d.cardsList.end(); ++ci) {
            std::cout << *ci << " ";
        }
        
        return os;
    }
};

#endif /* Deck_hpp */
