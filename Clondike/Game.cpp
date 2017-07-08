//
//  Game.cpp
//  Clondike
//
//  Created by Alex King on 6/27/17.
//  Copyright © 2017 Alex King. All rights reserved.
//

#include "Game.hpp"
#include <sstream>

Game::Game()
{
    Deck d = Deck();
    d.shuffle();
    Board b = Board(d);
    board = b;
}

Game::Game(Board b)
{
    board = b;
}

Board* Game::getBoard()
{
    return &board;
}

// TODO:
// the logic for UNDO and PLAY should be refactored into new functions, and then
// the gameloop function could work better
Status Game::executeCommand(Command command)
{
    switch (command.move) {
        case QUIT: {
            return OK;
        }
        case DRAW: {
            previous = board;
            drawCards();
            canUndo = true;
            return OK;
        }
        case HINT: {
            return OK;
        }
        case UNDO: {
            if (canUndo) {
                board = previous;
                canUndo = false;
                return OK;
            } else {
                return NO_UNDO;
            }
            break;
        }
        case SOLVE: {
            return OK;
        }
        case NEWGAME: {
            return OK;
        }
        case AUTO: {
            return OK;
        }
        case HELP: {
            return OK;
        }
        case UNKNOWN: {
            return UNRECOGNIZED;
        }
        case PLAY: {
            previous = board;
            bool result = makePlay(command.src, command.dst);
            if (result == false) return INVALID;
            else {
                bool finished = checkIfWon();
                if (finished) return WON;
                canUndo = true;
                return OK;
            }  
        }
    }
    return UNRECOGNIZED;
}

bool Game::checkIfWon()
{
    auto fs = board.foundations;
    return std::all_of(fs.begin(), 
                       fs.end(),
                       [](Foundation f){return f.size() == 13;});
}

// makePlay receives two Position definitions. It translates Positions
// to actual data addresses of cards to be moved.
bool Game::makePlay(Position src, Position dst)
{
    
    CardPile *srcPile, *dstPile;
    Card srcCard;
    int numCardsMoving = 0;
    int srcCardsLeftFaceUp = 0;
    
    switch (src.type) {
        case POS_DRAW: {
            srcPile = &board.draw;
            if (srcPile->size() == 0) return false;
            srcCard = srcPile->cardAtTop();
            
            numCardsMoving = 1;
            break;
        }
        case POS_FOUNDATION: {
            srcPile = &board.foundations.at(src.f - 1);
            srcCard = srcPile->cardAtTop();
            
            numCardsMoving = 1;
            break;
        }
        case POS_TABLEAU: {
            srcPile = &board.tableaus.at(src.t.col - 1);
            
            // if row specified is out of bounds
            if (src.t.row < 1 or src.t.row > srcPile->size()) return false;
            
            // if row specified is not yet uncovered
            if (src.t.row <=
                (srcPile->size() - srcPile->getNumCardsFaceUp())) return false;
            
            srcCard = srcPile->cardAt(src.t.row - 1);
            numCardsMoving = srcPile->size() - src.t.row + 1;
            if (numCardsMoving < srcPile->getNumCardsFaceUp()) {
                srcCardsLeftFaceUp = srcPile->getNumCardsFaceUp() - numCardsMoving;
            } else if (numCardsMoving == srcPile->size()) {
                srcCardsLeftFaceUp = 0;
            } else {
                srcCardsLeftFaceUp = 1;
            }
            break;
        }
    }
    
    switch (dst.type) {
        case POS_FOUNDATION: {
            dstPile = &board.foundations.at(dst.f - 1);
            break;
        }
        case POS_TABLEAU: {
            dstPile = &board.tableaus.at(dst.t.col - 1);
            break;
        }
    }
    
    if (dstPile->canPlaceCard(srcCard)) {
        moveCardRange(srcPile, dstPile, numCardsMoving);
        if (src.type == POS_TABLEAU) {
            srcPile->setNumCardsFaceUp(srcCardsLeftFaceUp);
        }
        if (dst.type == POS_TABLEAU) {
            dstPile->setNumCardsFaceUp(dstPile->getNumCardsFaceUp() + numCardsMoving);
        }
        return true;
    } else {
        return false;
    }
}

// Draw cards from the deck and hold face up
void Game::drawCards()
{
    int deckLength = board.deck.size();
    if (deckLength == 0) {
        dealCardRange(&board.draw, &board.deck, board.draw.size());
    } else {
        int cardsToDraw = (deckLength >= 3 ? 3 : deckLength);
        dealCardRange(&board.deck, &board.draw, cardsToDraw);
    }
}

std::vector<Command> Game::generateValidMoves()
{
    std::vector<Command> validMoves;
    
    // Check draw card against each tableau
    if (board.draw.size() > 0) {
        for (int i = 0; i < board.tableaus.size(); i++) {
            if (board.tableaus.at(i).canPlaceCard(board.draw.cardAtTop())) {
                // construct command
                Position src;
                src.type = POS_DRAW;
                
                Position dst;
                dst.type = POS_TABLEAU;
                dst.t.col = i + 1;
                dst.t.row = board.tableaus.at(i).size() + 1;
                Command move = { PLAY, src, dst };
                validMoves.push_back(move);
            }
        }
        // Check draw card against each foundation
        for (int i = 0; i < board.foundations.size(); i++) {
            if (board.foundations.at(i).canPlaceCard(board.draw.cardAtTop())) {
                // construct command
                Position src;
                src.type = POS_DRAW;
                
                Position dst;
                dst.type = POS_FOUNDATION;
                dst.f = Pos_Foundation(i) + 1;
                Command move = { PLAY, src, dst };
                validMoves.push_back(move);
            }
        }
    }

    // Check each tableau ending against each foundation
    for (int i = 0; i < board.tableaus.size(); i++) {
        if (board.tableaus.at(i).size() == 0) continue;
        for (int j = 0; j < board.foundations.size(); j++) {
            if (board.foundations.at(j).canPlaceCard(board.tableaus.at(i).cardAtTop())) {
                // construct command
                Position src;
                src.type = POS_TABLEAU;
                src.t.col = i + 1;
                src.t.row = board.tableaus.at(i).size();
                
                Position dst;
                dst.type = POS_FOUNDATION;
                dst.f = Pos_Foundation(j) + 1;
                Command move = { PLAY, src, dst };
                validMoves.push_back(move);
            }
        }

    }
    // Check each tableau substack against each tableau
    for (int i = 0; i < board.tableaus.size(); i++) { // source
        for (int j = 0; j < board.tableaus.size(); j++) { // destination
            if (i == j) continue;
            int size = board.tableaus.at(i).size();
            for (int k = (size - board.tableaus.at(i).getNumCardsFaceUp()); k < size; k++) {
                
                if (board.tableaus.at(j).canPlaceCard(board.tableaus.at(i).cardAt(k))) {
                    // construct command
                    Position src;
                    src.type = POS_TABLEAU;
                    src.t.col = i + 1;
                    src.t.row = k + 1;
                    
                    Position dst;
                    dst.type = POS_TABLEAU;
                    dst.t.col = j + 1;
                    dst.t.row = board.tableaus.at(j).size() + 1;
                    Command move = { PLAY, src, dst };
                    validMoves.push_back(move);
                }
            }

        }
        
    }
    return validMoves;
}

/*
 Moves specified number of cards from src to dst in "dealing" order,
 effectively reversing order
*/
void Game::dealCardRange(CardPile *src, CardPile *dst, int cardsToMove)
{
    while (cardsToMove--) {
        dst->addCard(src->dealFromTop());
    }
}

/*
 Moves specified number of cards from src to dst in original order,
 preserving order
*/
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
