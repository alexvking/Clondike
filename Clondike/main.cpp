//
//  main.cpp
//  Clondike
//
//  Created by Alex King on 6/27/17.
//  Copyright © 2017 Alex King. All rights reserved.
//

#include <iostream>
#include "Deck.hpp"
#include "Board.hpp"
#include "Game.hpp"

int main(int argc, const char * argv[]) {
    Deck d = Deck();
    d.shuffle();
    Board b = Board(d);
    Game g = Game(b);
    cout << b << std::endl;
    g.play();
    return 0;
}
