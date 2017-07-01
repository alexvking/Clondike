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
#include "Command.hpp"

enum Error { UNRECOGNIZED, INVALID, NO_UNDO };

class Game {
public:
    Game(Board b);
    bool drawCards();
    void play();
    void dealCardRange(CardPile *src, CardPile *dst, int cardsToMove);
    void moveCardRange(CardPile *src, CardPile *dst, int cardsToMove);
    void executeCommand(Command command);
    bool makePlay(Command command);
    void printErrorMessage(Error e);
    std::vector<Command> generateValidMoves();
    
    Command parseToken1(string token1);
    Command parsePlayTokens(string src_row, string src_col,
                            string dst_row, string dst_col);
    
    
    friend std::ostream &operator<<(std::ostream &os, Game &g) {
        return os << g.board;
    }
    
private:
    Board board;
    Board previous;
    int   hint;
    int   moves;
    int   lateralList;
    int   prev;
    bool  canUndo;
    bool  winnableIsKnown;
    int   score;
    
};

#endif /* Game_hpp */
