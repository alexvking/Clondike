//
//  Board.hpp
//  Clondike
//
//  Created by Alex King on 6/27/17.
//  Copyright © 2017 Alex King. All rights reserved.
//

#ifndef Board_hpp
#define Board_hpp

#include <stdio.h>
#include <vector>
#include "Deck.hpp"
#include "CardPile.hpp"
#include "Foundation.hpp"
#include "Tableau.hpp"

#define NUM_TABLEAUS 7
#define NUM_FOUNDATIONS 4
#define FOUNDATION_OFFSET 2
#define NUM_CARDS_DRAWN 3

using namespace std;

struct size_less
{
    template<class T> bool operator()(T &a, T &b) const
    { return a.size() < b.size(); }
};

class Board {
public:
    Board();
    Board(Deck d);
    int maxTableauLength();
    
    friend ostream &operator<<(ostream &os, Board &b);
    
    Deck                deck;
    vector<Tableau>     tableaus;
    vector<Foundation>  foundations;
    CardPile            draw;
};

#endif /* Board_hpp */
