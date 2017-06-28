//
//  Game.cpp
//  Clondike
//
//  Created by Alex King on 6/27/17.
//  Copyright © 2017 Alex King. All rights reserved.
//

#include "Game.hpp"

Game::Game(Board b)
{
    board = b;
}

void Game::play()
{
    char input;
    cin >> input;
    while (input != 'q') {
        // parse input
        drawCards();
        cout << board;
        cin >> input;
    }
    // Move move = parseInput(input);
    // executeMove(move);
}

// Draw cards from the deck and hold face up
// Returns True if the move is successful
bool Game::drawCards()
{
    int deckLength = board.deck.size();
    if (deckLength == 0) {
        // TEMPORARILY SKIPPING IS_OVER AND IS_WINNABLE
        // self.moves = 0
        moveCardRange(&board.draw, &board.deck, board.draw.size());
        board.deck.flip(); // flip over the cards???
        return true;
    } else {
        int cardsToDraw = (deckLength >= 3 ? 3 : deckLength);
        dealCardRange(&board.deck, &board.draw, cardsToDraw);
    }
    
    return true;
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
        std::cout << cardsToMove << std::endl;
    }
    while (!hold.isEmpty()) {
        dst->addCard(hold.dealFromTop());
    }
}
