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
#include "Card.hpp"
#include <vector>

class Tableau {
public:
    Tableau();
    bool isEmpty();
    bool isFull();
    bool addCard(Card c);
    int  size();
    void deal(Card c);
    Card cardAt(int i);

    friend std::ostream &operator<<(std::ostream &os, Tableau const &t) {
        for (auto ci = t.cardsList.begin(); ci != t.cardsList.end(); ++ci) {
            std::cout << *ci << " ";
        }
        
        return os;
    }
    
    int numCardsFaceUp;
private:
    std::vector<Card> cardsList;

};

#endif /* Tableau_hpp */
