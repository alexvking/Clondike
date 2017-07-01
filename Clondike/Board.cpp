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

ostream &operator<<(ostream &os, Board &b) {
    os << endl;
    os << "          01   02 03 04 05\n";
    os << "          \\/\n";
    if (b.deck.isEmpty()) {
        os << (COLOR ? "\033[44m" : "") << "[ ]" 
           << (COLOR ? "\033[0m" : "");
    } else {
        os << (COLOR ? "\033[44m" : "") << "[.]" 
           << (COLOR ? "\033[0m" : "");
    }

    os << " ";

    // Print up to three drawn cards
    for (int i = NUM_CARDS_DRAWN; i > 0; i--) {
        if (b.draw.size() >= i) {
            os << b.draw.cardAt(b.draw.size() - i);
        } else {
            os << "  ";
        }
        os << " ";
    }
    os << "  ";
    
    // Print accumulation piles
    for(auto& f: b.foundations) {
        if (f.size() > 0) {
            os << f.cardAt(f.size() - 1);
        } else {
            os << "__";
        }
        os << " ";
    }
    os << "\n\n";
    
    // Number the columns for ease of reference
    os << " ";
    for (int i = 1; i <= NUM_TABLEAUS; i++) {
        os << i;
        os << "   ";
    }
    os << "\n\n";
    
    // Find the largest column of working cards for array bounds
    int maxLength = b.maxTableauLength();
    
    // Print each column of cards one row at a time
    for (int row = 0; row < (maxLength + 1); row++) {
        for (auto& col: b.tableaus) {
            if (col.size() > row) {
                // If the card is uncovered, print its identity
                if ((col.size() - row) <= col.numCardsFaceUp) {
                    os << col.cardAt(row);
                } else {
                    os << (COLOR ? "\033[44m" : "") << "[]" 
                       << (COLOR ? "\033[0m" : "");
                }
                os << "  ";
            } else {
                os << "    ";
            }
            
        }
        os << "    " << (row + 1) << "\n";
    }
    return os;
}