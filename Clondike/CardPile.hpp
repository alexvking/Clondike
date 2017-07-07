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
#include <vector>

#include "Card.hpp"

class CardPile {
public:
    bool isEmpty();
    bool addCard(Card c);
    int  size();
    int  getNumCardsFaceUp();
    void setNumCardsFaceUp(int cardsFaceUp);
    virtual bool canPlaceCard(Card c);
    Card cardAt(int i);
    Card dealFromTop();
    Card cardAtTop();
    
protected:
    std::vector<Card> cardsList;
    int numCardsFaceUp;
};

#endif /* CardPile_hpp */
