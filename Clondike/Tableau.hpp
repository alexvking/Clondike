//
//  Tableau.hpp
//  Clondike
//
//  Created by Alex King on 6/27/17.
//  Copyright © 2017 Alex King. All rights reserved.
//

#ifndef Tableau_hpp
#define Tableau_hpp

#include <stdio.h>
#include "CardPile.hpp"
#include <vector>

class Tableau: public CardPile {
public:
    Tableau();
    bool isFull();
    virtual bool canPlaceCard(Card c);
    int  getNumCardsFaceUp();
    void setNumCardsFaceUp(int cardsFaceUp);
};

#endif /* Tableau_hpp */
