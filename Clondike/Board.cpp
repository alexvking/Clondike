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
            // Remember, addCard is the CardPile method to force add a card to a pile
            // for legal adding, check if placeCard works
            tableaus.at(i).addCard(d.dealFromTop());
        }
    }
    deck = d;
    for (int i = 0; i < 4; i++) {
        foundations.push_back(Foundation());
    }
}

int Board::maxTableauLength()
{
    return max_element(tableaus.begin(), tableaus.end(), size_less())->size();
}
