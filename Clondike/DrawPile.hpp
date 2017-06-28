//
//  DrawPile.hpp
//  Clondike
//
//  Created by Alex King on 6/27/17.
//  Copyright © 2017 Alex King. All rights reserved.
//

#ifndef DrawPile_hpp
#define DrawPile_hpp

#include <stdio.h>
#include "Card.hpp"
#include <vector>

class DrawPile {
public:
    bool isEmpty();
    bool addCard(Card c);
    int  size();
    Card cardAt(int i);
    
    friend std::ostream &operator<<(std::ostream &os, DrawPile const &d) {
        for (auto ci = d.cardsList.begin(); ci != d.cardsList.end(); ++ci) {
            std::cout << *ci << " ";
        }
        
        return os;
    }
    
private:
    std::vector<Card> cardsList;
};

#endif /* DrawPile_hpp */
