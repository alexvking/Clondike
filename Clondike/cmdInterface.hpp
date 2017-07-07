//
//  cmdInterface.hpp
//  Clondike
//
//  Created by Alex King on 6/30/17.
//  Copyright © 2017 Alex King. All rights reserved.
//

#ifndef cmdInterface_hpp
#define cmdInterface_hpp

#include <stdio.h>
#include <sstream>
#include <iostream>

#include "Command.hpp"
#include "Game.hpp"

// Toggle ON for Unix terminal colored printing, OFF for black and white
#define COLOR false

enum InputType { SINGLE_INPUT, MULTI_INPUT, UNKNOWN_INPUT };

struct Input {
    InputType input;
    Command command;
};

class GameInterface {
public:
    void launchGameLoop();
private:
    Game g;
    
    Command parseToken1(string token1);
    Position commandToPosition(string command);
    void    displayErrorMessage(Status status);
    void    updateView();
    void    printCard(Card c);
    void    displayHints();
    void    exitGame();
    void    autoPlay();
    
};

#endif /* cmdInterface_hpp */
