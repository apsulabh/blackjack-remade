/*
 *   Copyright (c) 2024 Sulabh Patel
 *   All rights reserved.
 */
#include "player.h"
#include <numeric>
#include <string>
using namespace std;

// Add constructor to initialize money
Player::Player(double initialMoney) : money(initialMoney) {}

void Player::playHand(Deck &deck, int bet) {
  string userChoice = "hit";
  int dealerTotal = 0;
  int doubleDownCounter; // counter to track if a player hit during an
                         // individual game, because you can only double down
                         // after seeing your first 2 cards, not after hitting.
  deck.reset();
  deck.shuffle();
  reset();
  hand.push_back(deck.dealCard());
  hand.push_back(deck.dealCard());
  dealerHand.push_back(deck.dealCard());
  dealerHand.push_back(deck.dealCard());
  cout << "Your hand is: " << endl;
  displayHand();
  cout << "The dealers first card is the: " << endl;
  cout << dealerHand[0].toString() << endl;

  if (handValue() == 21) { // if the hand is 21 we get blackjack so hit loop is not neccesary
    userChoice = "stand"; // we dont need to hit if we have blackjack, used so
                          // that next big while loop doesn't go off.
    cout << "Congrats! You got BlackJack! That means you win as long as the "
            "dealer doesn't get one too!"
         << endl;
    cout << "The dealers second card is the: " << dealerHand[1].toString()
         << endl;
    dealerTotal = dealerHandValue();
    if (dealerTotal != 21) {
      cout << "The dealer did not get a BlackJack! " << endl;
      cout << "You win 1.5x your bet because you won with a BlackJack, so you "
              "won: $"
           << bet * 1.5 << endl;
      money += bet * 1.5;
      return;
    } else {
      cout << "The dealer also got a BlackJack! You don't lose or gain anything"
           << endl;
      return;
    }
  }                      // CASE: YOU GOT BLACKJACK
  doubleDownCounter = 0; // ensures the next loop goes off properly with the
                         // choice to double down.
  while (userChoice !="stand") // CASE: YOU DIDNT GET BLACKJACK YOU HAVE CHOICES
  {
    if (doubleDownCounter == 0) {
      cout << "Would you like to hit, stand, or double down? ";
      cin >> userChoice;
      if (userChoice == "double_down") {
        if(money<bet*2)
        {
          cout<<"You don't have enough money to double down! Try again."<<endl;
          userChoice="Try Again";
        }
        else if(money>=bet*2){
        hand.push_back(deck.dealCard());
        cout << "Your double'd down card is: "
             << hand[hand.size() - 1].toString() << endl;
        cout << "So your total is: " << handValue() << endl;
        bet *= 2;
        if (handValue() > 21) {
          cout << "You busted on a double down! You lose twice your bet!"
               << endl;
          money -= bet;
          return;
        }
          doubleDownCounter =
            10; // CASE DOUBLE DOWN BUT NOT BUSTED, could equal any number at
                // all, used in if statement in line 111.
          break;
        }
      } else if (userChoice == "hit") {
        hand.push_back(deck.dealCard());
        cout << "Your card is: " << hand[hand.size() - 1].toString() << endl;
        cout << "So your total is: " << handValue() << endl;
        if (handValue() > 21) {
          cout << "You busted! You lose your bet!" << endl;
          money -= bet;
          return;
        }
        doubleDownCounter++;
      } else if (userChoice == "stand") {
        cout << "Your total is: " << handValue() << endl;
        break;
      } else {
        cout << "That is not a valid choice!" << endl;
      }
    } else // this occurs only if doubleDownCounter is not 0, meaning the user
           // hit, so we ask if they would like to hit or stand
    {
      cout << "Would you like to hit or stand? ";
      cin >> userChoice;
      if (userChoice == "hit") {
        hand.push_back(deck.dealCard());
        cout << "Your card is: " << hand[hand.size() - 1].toString() << endl;
        cout << "So your total is: " << handValue() << endl;
        if (handValue() > 21) {
          cout << "You busted! You lose your bet!" << endl;
          money -= bet;
          return;
        }
      } else if (userChoice == "stand") {
        cout << "Your total is: " << handValue() << endl;
        break;
      } else {
        cout << "Invalid choice, please try again" << endl;
      }
    }
  }
  if (handValue() <= 21) // CASE: IF YOU HAVENT BUSTED YET
  {
    cout << "The dealers second card is the: " << dealerHand[1].toString()
         << endl;
    dealerTotal = dealerHandValue();
    cout << "The dealers total is: " << dealerTotal << endl;
  }
  if (dealerTotal == 21) // CASE: IF THE DEALER HAS BLACKJACK, WE LOSE)
  {
    cout << "The dealer got a BlackJack! You lose!" << endl;
    money -= bet;
  }
  if (dealerTotal == 21 &&
      doubleDownCounter ==
          10) // CASE: IF THE DEALER HAS BLACKJACK AND YOU DOUBLED DOWN
  {
    cout << "The dealer got a BlackJack and you doubled down! You lose double "
            "your bet!"
         << endl;
    money -= bet; // only -= bet because bet was doubled when you doubled down.
  }
  while (dealerTotal <= 16) // CASE: DEALER HIT LOOP
  {
    dealerHand.push_back(deck.dealCard());
    cout << "The dealers Hits! The card is: "
         << dealerHand[dealerHand.size() - 1].toString() << endl;
    dealerTotal += dealerHand[dealerHand.size() - 1].getValue();
    cout << "This makes the dealer total: " << dealerTotal << endl;
  }
  if (dealerTotal > 21) // CASE:THE DEALER BUSTED AND WE ARE STILL IN
  {
    cout << "The dealer busted! You win!" << endl;
    money += bet;
  } else if (dealerTotal <= 21 &&
             dealerTotal > handValue()) // CASE: DEALER HAND IS BETTER THAN OURS
  {
    cout << "The dealer wins!" << endl;
    money -= bet;
  } else if (dealerTotal <= 21 && dealerTotal == handValue()) // CASE: TIE
  {
    cout << "You tied!" << endl;
  } else if (dealerTotal <= 21 &&
             dealerTotal < handValue()) // CASE: WE HAVE BETTER HAND THAN DEALER
  {
    cout << "You beat the dealer!" << endl;
    money += bet;
  } else {
    cout << "I DONT KNOW HOW I GOT HERE CODE IS BUGGED";
  }
}

// Add a method to calculate the total value of the player's hand.
int Player::handValue() const {
  int totalValue = 0;
  int aceCount = 0;
  for (const auto &card : hand) {
    totalValue += card.getValue();
    if (card.getValue() == Card::ACE) {
      aceCount++;
    }
  }
  // Adjust total value if ACE is present and the total value is greater than 21
  while (totalValue > 21 && aceCount > 0) {
    totalValue -= 10;
    aceCount--;
  }
  return totalValue;
}

// Add a method to add a card to the player's hand.
void Player::addCard(Card &newCard) { hand.push_back(newCard); }

// Add a method to return how much money player has
double Player::getMoney() { return money; }

// Add a method to display a hand.
void Player::displayHand() {
  for (const auto &card : hand) {
    cout << card.toString() << endl;
  }
  cout << endl;
}

// Displays dealer's hand.
void Player::displayDealerHand() {
  for (const auto &card : dealerHand) {
    cout << card.toString() << endl;
  }
  cout << endl;
}
void Player::reset() {
  hand.clear();
  dealerHand.clear();
}
int Player::dealerHandValue() const
{
  int totalValue = 0;
  int aceCount = 0;
  for (const auto &card : dealerHand) {
    totalValue += card.getValue();
    if (card.getValue() == Card::ACE) {
      aceCount++;
    }
  }
  // Adjust total value if ACE is present and the total value is greater than 21
  while (totalValue > 21 && aceCount > 0) {
    totalValue -= 10;
    aceCount--;
  }
  return totalValue;
}
