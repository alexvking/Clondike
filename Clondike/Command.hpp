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

// TODO: probably drop the "type" from this enum, maybe just rename it
enum MoveType { QUIT, DRAW, HINT, UNDO, SOLVE, AUTO, HELP, PLAY, UNKNOWN };

enum Status { OK, WON, UNRECOGNIZED, INVALID, NO_UNDO };

// Wish list: sew together key-value list of MoveType, StringList such that we can
// easily iterate over it to check if input is in StringList, in which case output Move
static std::vector<std::string> quitStrings  = {"q", "quit", "exit"};
static std::vector<std::string> autoStrings  = {"a", "auto", "autoplay"};
static std::vector<std::string> drawStrings  = {"d", "draw"};
static std::vector<std::string> hintStrings  = {"h", "hint"};
static std::vector<std::string> undoStrings  = {"u", "undo"};
static std::vector<std::string> solveStrings = {"s", "solve"};
static std::vector<std::string> helpStrings  = {"help"};

struct Command {
    MoveType move;
    int      srcCol;
    int      srcRow;
    int      dstCol;
    int      dstRow;
    
    friend ostream &operator<<(ostream &os, Command const &c);
};

#endif /* Command_hpp */
