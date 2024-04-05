// Each card gets a suit and value (2-10, J, Q, K, A)
// getValue method (returns the value of the card)
// getSuit method (returns the suit of the card)
#include "card.h"

std::string suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
std::string values[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10"};


Card::Card(Suit s, Value v) : suit(s), value(v) {}

Card::~Card() {
    suit = nullSuit;
    value = nullValue;
}

Card::Value Card::getValue() const {
  return value;
}

Card::Suit Card::getSuit() const {
  return suit;
}

std::string Card::toString() const {
  if(TWO <= value && value <= TEN) {
    return values[value - 2] + " of " + suits[suit];
  }else if (value == JACK) {
    return "Jack of " + suits[suit];
  }else if (value == QUEEN) {
    return "Queen of " + suits[suit];
  }else if (value == KING) {
    return "King of " + suits[suit];
  }else if (value == ACE) {
    return "Ace of " + suits[suit];
  }
  return 0; // Shouldn't happen (Non-void function does not return a value in all control paths)
}
