//
//  Game.cpp
//  Clondike
//
//  Created by Alex King on 6/27/17.
//  Copyright © 2017 Alex King. All rights reserved.
//

#include "Game.hpp"
#include <sstream>

Game::Game(Board b)
{
    board = b;
}

void Game::play()
{
    std::vector<std::string> tokens;
    string s = "";
    string token;

    // should be refactored
    // while (getCommand)
    // executeCommand()
    // then the cmdUI should be abstracted away from Game
    
    while (true) {
        std::getline(cin, s);
        std::stringstream tokenStream(s);
        while (tokenStream >> s) {
            tokens.push_back(s);
        }
        if (tokens.size() == 1) {
            Command command = parseToken1(tokens.at(0));
            executeCommand(command);
        } else if (tokens.size() == 4) {
            Command command = parsePlayTokens(tokens.at(0), tokens.at(1),
                                              tokens.at(2), tokens.at(3));
            executeCommand(command);
        } else {
            printErrorMessage(UNRECOGNIZED);
        }

        cout << board;
        tokens.clear();
    }
}

void Game::printErrorMessage(Error e)
{
    switch (e) {
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

void Game::executeCommand(Command command)
{
    switch (command.move) {
        case QUIT: {
            exit(0);
            break;
        }
        case DRAW: {
            drawCards();
            auto validMoves = generateValidMoves();
            for (auto & m : validMoves) {
                cout << m << endl;
            }
            break;
        }
        case HINT: {
            auto validMoves = generateValidMoves();
            for (auto & m : validMoves) {
                cout << m << endl;
            }
            break;
        }
        case UNDO: {
            if (canUndo) {
                board = previous;
                canUndo = false;
            } else {
                printErrorMessage(NO_UNDO);
            }
            break;
        }
        case SOLVE: {
            break;
        }
        case HELP: {
            // printHelp();
            break;
        }
        case PLAY: {
            bool result = makePlay(command);
            if (result == false) printErrorMessage(INVALID);
            canUndo = true;
            auto validMoves = generateValidMoves();
            for (auto & m : validMoves) {
                cout << m << endl;
            }
            break;
        }
    }
}

bool Game::makePlay(Command command)
{
    // Check that all coordinates are in bounds: rows 0-7 are valid, columns 1-?
    // depending on depth of board
    int srcCol = command.srcCol;
    int srcRow = command.srcRow;
    int dstCol = command.dstCol;
    int dstRow = command.dstRow;
    
    if (srcCol < 0 or srcCol > board.tableaus.size()) {
        return false;
    }
    if (dstCol < 0 or dstCol > board.tableaus.size()) {
        return false;
    }
    if (srcRow < 1 or srcRow > board.maxTableauLength()) {
        return false;
    }
    if (dstRow < 1 or dstRow > (board.maxTableauLength() + 1)) {
        return false;
    }
    
    // If destination is foundation
    // row and column are actually switched here from how the board is physically
    // displayed. This is because the first number sent is a "0", really indicating
    // "row 0"
    if (dstCol == 0) {
        int numCardsMoving = 1;
        if (dstRow < 2 or dstRow > 5) return false; // must be valid foundation
        
        // locate source card
        if (srcCol == 0) {
            if (srcRow == 1) {
                
                // draw card is source
                if (board.foundations.at(dstRow - 2).placeCard(board.draw.cardAtTop())) {
                    previous = board;
                    moveCardRange(&board.draw, &board.foundations.at(dstRow - 2), numCardsMoving);
                    return true;
                }
            } else if (srcRow >= 2 and srcRow <= 5) { // TODO: IS THIS A REDUNDANT CHECK, GIVEN THAT
                                                        // WE CHECK BOUNDS ABOVE?
                // foundation is source
                return false; // can never move cards between foundations
            }
        }
        else if (srcCol >= 1 and srcCol <=7) {
            // a tableau is the source...
            // if not the last card in the stack, not legal
            if (srcRow != board.tableaus.at(srcCol - 1).size()) return false;
            
            if (board.foundations.at(dstRow - 2).placeCard(board.tableaus.at(srcCol - 1).cardAt(srcRow - 1))) {
                previous = board;
                moveCardRange(&board.tableaus.at(srcCol - 1), &board.foundations.at(dstRow - 2), numCardsMoving);
                if (board.tableaus.at(srcCol - 1).numCardsFaceUp != 1) {
                    board.tableaus.at(srcCol - 1).numCardsFaceUp -= 1;
                }
                return true;
            }
        }
    }
    // If destination is tableau
    else if (dstCol > 0 and dstCol <= board.maxTableauLength()) {
        
        // locate source card
        if (srcCol == 0) {
            if (srcRow == 1) {
                // draw card is source
                int numCardsMoving = 1;
                if (board.tableaus.at(dstCol - 1).placeCard(board.draw.cardAtTop())) {
                    previous = board;
                    moveCardRange(&board.draw, &board.tableaus.at(dstCol - 1), numCardsMoving);
                    board.tableaus.at(dstCol - 1).numCardsFaceUp += numCardsMoving;
                    return true;
                }
                
            } else if (srcCol >= 2 and srcCol <= 5) {
                // foundation is source
                int numCardsMoving = 1;
                if (board.tableaus.at(dstCol - 1).placeCard(board.foundations.at(srcRow).cardAtTop())) {
                    previous = board;
                    moveCardRange(&board.foundations.at(srcRow), &board.tableaus.at(dstCol - 1), numCardsMoving);
                    board.tableaus.at(dstCol - 1).numCardsFaceUp += numCardsMoving;
                    return true;
                }
            }
        }
        else { // if (srcRow >= 1 and srcRow <=7) {
            // a tableau is the source
            int numCardsMoving = board.tableaus.at(srcCol - 1).size() - srcRow + 1;
            if (board.tableaus.at(dstCol - 1).placeCard(board.tableaus.at(srcCol - 1).cardAt(srcRow - 1))) {
                previous = board;
                moveCardRange(&board.tableaus.at(srcCol - 1), &board.tableaus.at(dstCol - 1), numCardsMoving);
                board.tableaus.at(dstCol - 1).numCardsFaceUp += numCardsMoving;
                board.tableaus.at(srcCol - 1).numCardsFaceUp -= numCardsMoving;
                if (board.tableaus.at(srcCol - 1).numCardsFaceUp != 1) {
                    board.tableaus.at(srcCol - 1).numCardsFaceUp = 1;
                }
                return true;
            }
            
        }
    }
    
    return false;
}

Command Game::parseToken1(string token1)
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
        
        exit(1); return Command { QUIT };
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
        return Command { PLAY };
    }
}

Command Game::parsePlayTokens(string srcRow, string srcCol,
                              string dstRow, string dstCol)
{
    int srcRowToken = atoi(srcRow.c_str());
    int srcColToken = atoi(srcCol.c_str());
    int dstRowToken = atoi(dstRow.c_str());
    int dstColToken = atoi(dstCol.c_str());
    
    return Command { PLAY, srcRowToken, srcColToken, dstRowToken, dstColToken };
}

// Draw cards from the deck and hold face up
// Returns True if the move is successful
bool Game::drawCards()
{
    int deckLength = board.deck.size();
    if (deckLength == 0) {
        // TEMPORARILY SKIPPING IS_OVER AND IS_WINNABLE
        // self.moves = 0
        dealCardRange(&board.draw, &board.deck, board.draw.size());
        return true;
    } else {
        int cardsToDraw = (deckLength >= 3 ? 3 : deckLength);
        dealCardRange(&board.deck, &board.draw, cardsToDraw);
    }
    
    return true;
}

std::vector<Command> Game::generateValidMoves()
{
    std::vector<Command> validMoves;
    
    // Check draw card against each tableau
    if (board.draw.size() > 0) {
        for (int i = 0; i < board.tableaus.size(); i++) {
            if (board.tableaus.at(i).placeCard(board.draw.cardAtTop())) {
                // construct command
                Command move = { PLAY, 0, 1, (i + 1), board.tableaus.at(i).size() };
                validMoves.push_back(move);
            }
        }
        // Check draw card against each foundation
        for (int i = 0; i < board.foundations.size(); i++) {
            if (board.foundations.at(i).placeCard(board.draw.cardAtTop())) {
                // construct command
                Command move = { PLAY, 0, 1, 0, (i + 2) };
                validMoves.push_back(move);
            }
        }
    }

    // Check each tableau ending against each foundation
    for (int i = 0; i < board.tableaus.size(); i++) {
        for (int j = 0; j < board.foundations.size(); j++) {
            if (board.foundations.at(j).placeCard(board.tableaus.at(i).cardAtTop())) {
                // construct command
                Command move = { PLAY, (i + 1), board.tableaus.at(i).size(), 0, (j + 2) };
                validMoves.push_back(move);
            }
        }

    }
    // Check each tableau substack against each tableau
    for (int i = 0; i < board.tableaus.size(); i++) { // source
        for (int j = 0; j < board.tableaus.size(); j++) { // destination
            if (i == j) continue;
            int size = board.tableaus.at(i).size();
            for (int k = (size - board.tableaus.at(i).numCardsFaceUp); k < size; k++) {
                
                if (board.tableaus.at(j).placeCard(board.tableaus.at(i).cardAt(k))) {
                    // construct command
                    Command move = { PLAY, (i + 1), (k + 1), (j + 1), (board.tableaus.at(j).size() + 1) };
                    validMoves.push_back(move);
                }
            }

        }
        
    }
    
    
    return validMoves;
}

void Game::dealCardRange(CardPile *src, CardPile *dst, int cardsToMove)
{
    while (cardsToMove--) {
        dst->addCard(src->dealFromTop());
    }
}

void Game::moveCardRange(CardPile *src, CardPile *dst, int cardsToMove)
{
    CardPile hold;
    while (cardsToMove--) {
        hold.addCard(src->dealFromTop());
    }
    while (!hold.isEmpty()) {
        dst->addCard(hold.dealFromTop());
    }
}
