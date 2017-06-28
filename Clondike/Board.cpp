//
//  Board.cpp
//  Clondike
//
//  Created by Alex King on 6/27/17.
//  Copyright © 2017 Alex King. All rights reserved.
//

#include "Board.hpp"

Board::Board()
{
    return;
}

Board::Board(Deck d)
{
    for (int i = 0; i < 7; i++) {
        tableaus.push_back(Tableau());
        for (int j = 0; j < i + 1; j++) {
            tableaus.at(i).addCard(d.dealFromTop());
        }
    }
//    cout << "Deck is of length " << d.size() << endl;
    deck = d;
    
}
