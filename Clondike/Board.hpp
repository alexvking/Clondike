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
#include "Deck.hpp"
#include "CardPile.hpp"
#include "Foundation.hpp"
#include "Tableau.hpp"
#include <vector>

using namespace std;

// Should this go somewhere else?
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
    
    friend ostream &operator<<(ostream &os, Board &b) {
        os << endl;
        os << "          01   02 03 04 05\n";
        os << "          \\/\n";
        if (b.deck.isEmpty()) {
            os << (COLOR ? "\033[44m" : "") << "[ ]" << (COLOR ? "\033[0m" : "");
        } else {
            os << (COLOR ? "\033[44m" : "") << "[.]" << (COLOR ? "\033[0m" : "");
        }

        os << " ";

        // Print up to three drawn cards
        for (int i = 3; i > 0; i--) {
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
        for (int i = 1; i < 8; i++) {
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
                        os << (COLOR ? "\033[44m" : "") << "[]" << (COLOR ? "\033[0m" : "");
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
    
    Deck deck;
    vector<Tableau> tableaus;
    vector<Foundation> foundations;
    CardPile draw;
};



#endif /* Board_hpp */
