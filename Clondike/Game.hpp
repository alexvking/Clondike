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

class Game {
public:
    Game();
    Game(Board b);
    void drawCards();
    void dealCardRange(CardPile *src, CardPile *dst, int cardsToMove);
    void moveCardRange(CardPile *src, CardPile *dst, int cardsToMove);
    Status executeCommand(Command command);
    bool makePlay(Position src, Position dst);
    bool checkIfWon();
    std::vector<Command> generateValidMoves();
    
    Board* getBoard();
    
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
