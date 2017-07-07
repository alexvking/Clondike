//
//  Command.cpp
//  Clondike
//
//  Created by Alex King on 6/28/17.
//  Copyright © 2017 Alex King. All rights reserved.
//

#include "Command.hpp"

ostream &operator<<(ostream &os, Command const &c) {
    switch (c.src.type) {
        case POS_DRAW: {
            os << "DC";
            break;
        }
        case POS_FOUNDATION: {
            os << "F" << c.src.f;
            break;
        }
            
        case POS_TABLEAU: {
            os << c.src.t.col << "," << c.src.t.row;
            break;
        }
    }
    os << " --> ";
    switch (c.dst.type) {
        case POS_FOUNDATION: {
            os << "F" << c.dst.f;
            break;
        }
            
        case POS_TABLEAU: {
            os << c.dst.t.col << "," << c.dst.t.row << " ";
            break;
        }
    }
    return os;
}
