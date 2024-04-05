// Each card gets a suit and value (2-10, J, Q, K, A)
// getValue method (returns the value of the card)
// getSuit method (returns the suit of the card)
#ifndef CARD_H
#define CARD_H

#include <string>
#include <iostream>

class Card {
public:
    enum Suit {nullSuit = -1, HEARTS = 0, DIAMONDS, CLUBS, SPADES};
    enum Value {nullValue = -1, TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK = 10, QUEEN = 10, KING = 10, ACE = 11};
    Card(Suit s, Value v);
    // Function Constructs a Card with a suit and a value
    // Pre: s must be one of the defined suits, v must be one of the defined values
    // Post: A Card object is created with the specified suit and value
    ~Card();
    // Function: Destructor
    // Pre: Card object is initialized
    // Post: Card is destroyed and its resources are deallocated (if any)
    Value getValue() const;
    // Function: Returns the value of the card
    // Pre: Card object is initialized
    // Post: The value of the card is returned
    Suit getSuit() const;
    // Function: Returns the suit of the card
    // Pre: Card object is initialized
    // Post: The suit of the card is returned
    std::string toString() const;
    // Function: Returns a string representation of the card
    // Pre: Card object is initialized
    // Post: A string representing the card (e.g., "Ace of Hearts") is returned
private:
      Suit suit;  // The Suit of the card
      Value value; // The Value of the card
};

#endif //CARD_H