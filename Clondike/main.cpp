//
//  main.cpp
//  Clondike
//
//  Created by Alex King on 6/27/17.
//  Copyright © 2017 Alex King. All rights reserved.
//

#include <iostream>
#include "Card.hpp"
#include "Deck.hpp"
#include "Board.hpp"

int main(int argc, const char * argv[]) {
    Card c = Card(RANK_J, HEART);
    std::cout << c << std::endl;
    Deck d = Deck();
    d.shuffle();
    std::cout << d;
    std::cout << "Hello, World!\n";
    
    Board b = Board(d);
    cout << b << std::endl;
    return 0;
}
