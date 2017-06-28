//
//  Foundation.hpp
//  Clondike
//
//  Created by Alex King on 6/27/17.
//  Copyright © 2017 Alex King. All rights reserved.
//

#ifndef Foundation_hpp
#define Foundation_hpp

#include <stdio.h>
#include "CardPile.hpp"
#include <vector>

class Foundation: public CardPile {
public:
    Foundation();
    bool isFull();
    bool placeCard(Card c);
        
    friend std::ostream &operator<<(std::ostream &os, Foundation const &f) {
        for (auto ci = f.cardsList.begin(); ci != f.cardsList.end(); ++ci) {
            std::cout << *ci << " ";
        }
        return os;
    }
    
private:
    Suit suit;
};

#endif /* Foundation_hpp */
