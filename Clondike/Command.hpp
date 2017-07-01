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

#endif /* Command_hpp */

using namespace std;

enum MoveType { QUIT, DRAW, HINT, UNDO, SOLVE, HELP, PLAY };

static std::vector<std::string> quitStrings  = {"q", "quit", "exit"};
static std::vector<std::string> drawStrings  = {"d", "draw"};
static std::vector<std::string> hintStrings  = {"h", "hint"};
static std::vector<std::string> undoStrings  = {"u", "undo"};
static std::vector<std::string> solveStrings = {"s", "solve"};
static std::vector<std::string> helpStrings  = {"help"};


// Wish list: sew together key-value list of MoveType, StringList such that we can
// easily iterate over it to check if input is in StringList, in which case output Move

struct Command {
    MoveType  move;
    int       srcCol;
    int       srcRow;
    int       dstCol;
    int       dstRow;
    
    friend ostream &operator<<(ostream &os, Command const &c);
};
