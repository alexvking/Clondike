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
    bool placeCard(Card c);
    friend std::ostream &operator<<(std::ostream &os, Tableau const &t) {
        for (auto ci = t.cardsList.begin(); ci != t.cardsList.end(); ++ci) {
            std::cout << *ci << " ";
        }
        
        return os;
    }
    int numCardsFaceUp;
};

#endif /* Tableau_hpp */
