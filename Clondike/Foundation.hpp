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
#include "Card.hpp"
#include <vector>

class Foundation {
public:
    Foundation();
    bool isEmpty();
    bool isFull();
    bool addCard(Card c);
    int  size();
    Card cardAt(int i);
        
    friend std::ostream &operator<<(std::ostream &os, Foundation const &f) {
        for (auto ci = f.cardsList.begin(); ci != f.cardsList.end(); ++ci) {
            std::cout << *ci << " ";
        }
        
        return os;
    }
    
private:
    Suit suit;
    std::vector<Card> cardsList;
};

#endif /* Foundation_hpp */
