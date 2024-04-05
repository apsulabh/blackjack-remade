#include <iostream>
#include "player.h"
#include <string>
using namespace std;


int main() 
{
  double initialMoney=0;
  int bet;
  string keepPlaying="yes";
  std::cout<<"Hi welcome to BlackJack! How much money would you like to start out with? ";
  while(initialMoney<=0)
    {
  cin>>initialMoney;
  if(initialMoney<=0)
  {
    cout<<"Please enter a valid amount of money: ";
  }
    }
  Player player(initialMoney);
  Deck deck;
  while(keepPlaying!="no")
    {
      bet=-1; //To ensure proper bet loop
      while(bet<=0||bet>player.getMoney())
        {
          cout<<"How much would you like to bet: ";
          cin>>bet;
          if(bet<0)
          {
            cout<<"You can't bet negative money! Try again."<<endl;
          }
          else if(bet>player.getMoney())
          {
            cout<<"You don't have that much money! Try again."<<endl;
          }
          else if(bet==0)
          {
            cout<<"You can't bet zero money! Try again."<<endl;
          }
          else
          {
            break;
          }
        }
      player.playHand(deck,bet);
      if(player.getMoney()==0) //money can't be less than 0
      {
        cout<<"You are out of money. Goodbye! ";
        break;
      } else if (player.getMoney()<0)
      {
        cout<<"You are in debt! Looks like the casino owns you. Goodbye! ";
        break;
      }
      cout<<"Your current balance is: "<<player.getMoney()<<endl;
      cout<<" Would you like to play again? "<<endl;
      cin>>keepPlaying;
    }
  cout<<"Thank you for playing BlackJack, we hope to see you again soon!"<<endl;
  return 0;
}