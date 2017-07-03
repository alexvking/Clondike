//
//  Board.cpp
//  Clondike
//
//  Created by Alex King on 6/27/17.
//  Copyright © 2017 Alex King. All rights reserved.
//

#include "Board.hpp"

struct size_less
{
    template<class T> bool operator()(T &a, T &b) const
    { return a.size() < b.size(); }
};

Board::Board()
{
    return;
}

Board::Board(Deck d)
{
    for (int i = 0; i < NUM_TABLEAUS; i++) {
        tableaus.push_back(Tableau());
        for (int j = 0; j < i + 1; j++) {
            tableaus.at(i).addCard(d.dealFromTop());
        }
    }
    deck = d;
    for (int i = 0; i < NUM_FOUNDATIONS; i++) {
        foundations.push_back(Foundation());
    }
}

int Board::maxTableauLength()
{
    return max_element(tableaus.begin(), tableaus.end(), size_less())->size();
}
