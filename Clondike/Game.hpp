//
//  Game.hpp
//  Clondike
//
//  Created by Alex King on 6/27/17.
//  Copyright © 2017 Alex King. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include "Board.hpp"

class Game {
public:
    Game(Board b);
    bool drawCards();
    void dealCardRange(CardPile *src, CardPile *dst, int cardsToMove);
    void moveCardRange(CardPile *src, CardPile *dst, int cardsToMove);
    void play();
    
    friend std::ostream &operator<<(std::ostream &os, Game &g) {
        return os << g.board;
    }
    
private:
    Board board;
    int   hint;
    int   moves;
    int   lateralList;
    int   prev;
    bool  canUndo;
    bool  winnableIsKnown;
    int   score;
    
};

#endif /* Game_hpp */
