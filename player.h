#ifndef PLAYER_H
#define PLAYER_H
#include "deck.h"
#include <string>
#include <vector>
class Player {
public:
  Player(); //Default Constructor
  Player(double initialMoney);
// Constructor that initializes a player with a given amount of money
// Pre: initialMoney must be greater or equal to zero
// Post: A Player object is created with the specified initial money
  void playHand(Deck &deck, int bet);
// Executes a single hand of blackjack for the player
// Pre: deck must be initialized and bet must be greater than zero.
// Post: The player plays a hand, and money is adjusted according to game result
  void displayHand();
// Displays the player's current hand to the console
// Pre: None
// Post: The player's hand is printed to the console
  void displayDealerHand();
// Displays the dealer's current hand to the console
// Pre: None
// Post: The dealer's hand is printed to the console
  void addCard(Card &newCard);
// Adds a card to the player's hand
// Pre: newCard must be a valid card object
// Post: The card is added to the player's current hand
  void reset();
// Resets the player's and dealer's hands to be empty
// Pre: None
// Post: The player and dealer hands are cleared
  int handValue() const;
// Calculates and returns the total value of the player's hand
// Pre: None
// Post: The total value of the player's hand is returned, accounting for Aces properly 
  int dealerHandValue() const;
// Calculates and returns the total value of the dealer's hand
// Pre: None
// Post: The total value of the dealer's hand is returned, accounting for Aces properly
  double getMoney();
// Returns the player's current money
// Pre: Money is >=0
// Post: The current amount of money the player has is returned

private:
  std::vector<Card> hand; // A vector that holds the cards of the players hand
  std::vector<Card> dealerHand; // A vector that holds the cards of the dealer
  double money; // Amount of money that the player has.
};
#endif // PLAYER_H