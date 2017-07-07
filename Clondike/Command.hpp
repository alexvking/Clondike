//
//  Command.hpp
//  Clondike
//
//  Created by Alex King on 6/28/17.
//  Copyright © 2017 Alex King. All rights reserved.
//

#ifndef Command_hpp
#define Command_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

/* A foundation position is an integer 1-4 inclusive */
typedef int Pos_Foundation;

/* A tableau position is a column 1-7 identifying the tableau, and a row identifying
   the card(s) 
 */
struct Pos_Tableau {
    int col;
    int row;
};

/* Accessible cards are therefore either the top card of the draw pile, any 
   foundation position, and any tableau position 
 */
enum PositionType { POS_DRAW, POS_FOUNDATION, POS_TABLEAU };

/* The position structure allows us to pick between them and access the data that we
   need
 */
struct Position {
    PositionType type;
    union {
        Pos_Foundation f;
        Pos_Tableau t;
    };
};


enum CommandType { QUIT, DRAW, HINT, UNDO, SOLVE, AUTO, HELP, PLAY, UNKNOWN };


enum Status { OK, WON, UNRECOGNIZED, INVALID, NO_UNDO };

static vector<string> quitStrings  = {"q", "quit", "exit"};
static vector<string> autoStrings  = {"a", "auto", "autoplay"};
static vector<string> drawStrings  = {"d", "draw"};
static vector<string> hintStrings  = {"h", "hint"};
static vector<string> undoStrings  = {"u", "undo"};
static vector<string> solveStrings = {"s", "solve"};
static vector<string> helpStrings  = {"help"};

struct Command {
    CommandType move;
    Position src;
    Position dst;
    
    friend ostream &operator<<(ostream &os, Command const &c);
};

#endif /* Command_hpp */
