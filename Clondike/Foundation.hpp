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
#include <vector>

#include "CardPile.hpp"

class Foundation: public CardPile {
public:
    bool isFull();
    bool placeCard(Card c);
};

#endif /* Foundation_hpp */
