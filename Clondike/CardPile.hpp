//
//  CardPile.hpp
//  Clondike
//
//  Created by Alex King on 6/27/17.
//  Copyright © 2017 Alex King. All rights reserved.
//

#ifndef CardPile_hpp
#define CardPile_hpp

#include <stdio.h>
#include "Card.hpp"
#include <vector>

class CardPile {
public:
    bool isEmpty();
    bool addCard(Card c);
    int  size();
    Card cardAt(int i);
    Card dealFromTop();
    
protected:
    std::vector<Card> cardsList;
};

#endif /* CardPile_hpp */
