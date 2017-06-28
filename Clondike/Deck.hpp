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
#include "Card.hpp"
#include <vector>

class Deck {
public:
    Deck();
    
    bool isEmpty();
    void shuffle();
    Card dealFromTop();

    friend std::ostream &operator<<(std::ostream &os, Deck const &d) {
        for (auto ci = d.cardsList.begin(); ci != d.cardsList.end(); ++ci) {
            std::cout << *ci << " ";
        }
        
        return os;
    }
    
private:
    std::vector<Card> cardsList;
    
};

#endif /* Deck_hpp */
