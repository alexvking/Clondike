//
//  Command.cpp
//  Clondike
//
//  Created by Alex King on 6/28/17.
//  Copyright © 2017 Alex King. All rights reserved.
//

#include "Command.hpp"

ostream &operator<<(ostream &os, Command const &c) {
    os << c.srcCol << " " << c.srcRow << " --> " << c.dstCol << " " << c.dstRow;
    return os;
}