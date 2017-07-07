//
//  cmdInterface.cpp
//  Clondike
//
//  Created by Alex King on 6/30/17.
//  Copyright © 2017 Alex King. All rights reserved.
//

#include <regex>
#include <string>

#include "cmdInterface.hpp"

void GameInterface::launchGameLoop()
{
    g = Game();
    updateView();
    std::vector<std::string> tokens;
    string s = "";
    string token;
    
    while (true) {
        std::getline(cin, s);
        std::transform(s.begin(), s.end(), s.begin(), ::tolower);
        Command command;
        Status status;
        
        std::regex playPattern("([1-7],\\d+|DC|F[1-4]) ([1-7],\\d+|DC|F[1-4])");
        std::smatch playMatch;
        
        std::regex controlPattern("([a-z]+)");
        std::smatch controlMatch;
        
        // User inputted integers
        if (std::regex_match(s, playMatch, playPattern)) {
            Position src = commandToPosition(playMatch[1]);
            Position dst = commandToPosition(playMatch[2]);
            command = Command { PLAY, src, dst };
            status = g.executeCommand(command);

        // User inputted a single command
        } else if (std::regex_match(s, controlMatch, controlPattern)) {
            command = parseToken1(controlMatch[0]);
            status = g.executeCommand(command);
        } else {
            status = UNRECOGNIZED;
        }

        switch (status) {
            case OK: {
                switch (command.move) {
                    case PLAY:
                        if (g.checkIfWon()) {
                            exitGame();
                        }
                        displayHints();
                        updateView();
                        break;
                    case DRAW:
                        displayHints();
                        updateView();
                        break;
                    case AUTO:
                        autoPlay();
                        break;
                    case UNDO:
                        displayHints();
                        updateView();
                        break;
                    case HINT:
                        displayHints();
                        break;
                    case SOLVE:
                        break;
                    case HELP:
                        break;
                    case QUIT:
                        exitGame();
                        return;
                }
                break;
            }

            case WON:
                exitGame();
                return;
            case UNRECOGNIZED:
                displayErrorMessage(UNRECOGNIZED);
                break;
            case INVALID:
                displayErrorMessage(INVALID);
                break;
            case NO_UNDO:
                displayErrorMessage(NO_UNDO);
                break;
            default:
                displayErrorMessage(UNRECOGNIZED);
                break;
        }
    }
}

Command GameInterface::parseToken1(string token1)
{
    std::transform(token1.begin(), token1.end(), token1.begin(), ::tolower);
    if (std::find(helpStrings.begin(), helpStrings.end(), token1)
        != helpStrings.end()) {
        
        return Command { HELP };
    } else if (std::find(hintStrings.begin(), hintStrings.end(), token1)
               != hintStrings.end()) {
        
        return Command { HINT };
    } else if (std::find(quitStrings.begin(), quitStrings.end(), token1)
               != quitStrings.end()) {
        
        return Command { QUIT };
    } else if (std::find(autoStrings.begin(), autoStrings.end(), token1)
               != autoStrings.end()) {
        
        return Command { AUTO };
    } else if (std::find(drawStrings.begin(), drawStrings.end(), token1)
               != drawStrings.end()) {
        
        return Command { DRAW };
    } else if (std::find(undoStrings.begin(), undoStrings.end(), token1)
               != undoStrings.end()) {
        
        return Command { UNDO };
    } else if (std::find(solveStrings.begin(), solveStrings.end(), token1)
               != solveStrings.end()) {
        
        return Command { SOLVE };
    } else {
        // TODO: this shouldn't be the else case, there should be one more
        return Command { PLAY };
    }
}

// TODO: Incomplete. Must rely on not repeating hints
void GameInterface::autoPlay()
{
    int tries = 3;
    while (!g.checkIfWon() and tries > 0)
    {
        auto validMoves = g.generateValidMoves();
        if (validMoves.size() > 0) {
            g.executeCommand(validMoves.at(0));
            tries = 3;
        }
        else {
            g.executeCommand(Command { DRAW });
            tries--;
        }
        updateView();
    }
    if (tries == 0) cout << "Failure.\n";
    else cout << "Success!\n";
}

// Takes string input of positions and converts them to Position structures
// commandToPosition
Position GameInterface::commandToPosition(string command)
{
    Position position;
    
    std::regex tableauPattern("(\\d),(\\d+)");
    std::smatch tableauMatch;
    std::regex foundationPattern("F([1-4])");
    std::smatch foundationMatch;

    if (std::regex_match(command, tableauMatch, tableauPattern)) {
        int colIndex = std::atoi(tableauMatch[1].str().c_str());
        int rowIndex = std::atoi(tableauMatch[2].str().c_str());
        position.type = POS_TABLEAU;
        position.t = Pos_Tableau { colIndex, rowIndex };

    } else if (command == "DC") {
        position.type = POS_DRAW;

    } else if (std::regex_match(command, foundationMatch, foundationPattern)) {
        Pos_Foundation colIndex = atoi(foundationMatch[1].str().c_str());
        position.type = POS_FOUNDATION;
        position.f = colIndex;
    }
    return position;
}

void GameInterface::displayErrorMessage(Status s)
{
    switch (s) {
        case UNRECOGNIZED:
            cout << "Error: unrecognized input.\n";
            break;
        case INVALID:
            cout << "Error: invalid coordinates. That move isn't legal.\n";
            break;
        case NO_UNDO:
            cout << "Error: cannot undo. You must have a previous state to revert to.";
            break;
        default:
            cout << "Error.\n";
            break;
    }
}

void GameInterface::updateView()
{
    Board* b = g.getBoard();
    cout << endl;
    cout << "          DC   F1 F2 F3 F4\n";
    cout << "          \\/\n";
    if (b->deck.isEmpty()) {
        cout << (COLOR ? "\033[44m" : "") << "[ ]"
           << (COLOR ? "\033[0m" : "");
    } else {
        cout << (COLOR ? "\033[44m" : "") << "[.]" 
           << (COLOR ? "\033[0m" : "");
    }

    cout << " ";

    // Print up to three drawn cards
    for (int i = NUM_CARDS_DRAWN; i > 0; i--) {
        if (b->draw.size() >= i) {
            printCard(b->draw.cardAt(b->draw.size() - i));
        } else {
            cout << "  ";
        }
        cout << " ";
    }
    cout << "  ";
    
    // Print accumulation piles
    for(auto& f: b->foundations) {
        if (f.size() > 0) {
            printCard(f.cardAt(f.size() - 1));
        } else {
            cout << "__";
        }
        cout << " ";
    }
    cout << "\n\n";
    
    // Number the columns for ease of reference
    cout << " ";
    for (int i = 1; i <= NUM_TABLEAUS; i++) {
        cout << i;
        cout << "   ";
    }
    cout << "\n\n";
    
    // Find the largest column of working cards for array bounds
    int maxLength = b->maxTableauLength();
    
    // Print each column of cards one row at a time
    for (int row = 0; row < (maxLength + 1); row++) {
        for (auto& col: b->tableaus) {
            if (col.size() > row) {
                // If the card is uncovered, print its identity
                if ((col.size() - row) <= col.getNumCardsFaceUp()) {
                    printCard(col.cardAt(row));
                } else {
                    cout << (COLOR ? "\033[44m" : "") << "[]" 
                       << (COLOR ? "\033[0m" : "");
                }
                cout << "  ";
            } else {
                cout << "    ";
            }
        }
        cout << "    " << (row + 1) << "\n";
    }
}

void GameInterface::printCard(Card c)
{
    switch (c.suit) {
        case HEART:
            cout << (COLOR ? "\033[32;41m" : "") << rankNames[c.rank] 
               << suitNames[c.suit] << (COLOR ? "\033[0m" : "");
            break;
        case SPADE:
            cout << (COLOR ? "\033[36;40m" : "") << rankNames[c.rank] 
               << suitNames[c.suit] << (COLOR ? "\033[0m" : "");
            break;
        case CLUB:
            cout << (COLOR ? "\033[33;40m" : "") << rankNames[c.rank] 
               << suitNames[c.suit] << (COLOR ? "\033[0m" : "");
            break;
        case DIAMOND:
            cout << (COLOR ? "\033[37;41m" : "") << rankNames[c.rank] 
               << suitNames[c.suit] << (COLOR ? "\033[0m" : "");
            break;
        default:
            break;
    }
}

void GameInterface::displayHints()
{
    auto validMoves = g.generateValidMoves();
    if (validMoves.size() == 0) {
        cout << "No moves available! Try drawing more cards.\n";
    }
    for (auto & m : validMoves) {
        cout << m << endl;
    }
}

void GameInterface::exitGame()
{
    cout << "Thanks for playing!\n";
}
