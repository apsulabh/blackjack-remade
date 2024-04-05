#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <stack>
#include <vector>
#include <algorithm>
#include <random>
class Deck {
public:
    Deck();
    // Constructor initializes a new deck of cards in sorted order
    void shuffle();
    // Function: Shuffles the deck of cards to randomize their order
    // Pre: Deck must be initialized
    // Post: The cards are shuffled
    Card dealCard();
    // Function: Deals the top card from the deck
    // Pre: Deck must not be empty and is initialized
    // Post: The top card is removed from the deck and returned
    void reset();
    // Function: Resets the deck to the original sorted state with all 52 cards
    // Pre: Deck is initialized
    // Post: Deck is in sorted state with all cards
private:
    std::stack<Card> cards;
    // A stack data structure to hold the cards. The stack allows easy addition and removal from the "top" of the deck as done in BlackJack.
};

#endif // DECK_H
