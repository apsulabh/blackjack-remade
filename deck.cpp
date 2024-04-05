/*
 *   Copyright (c) 2024 Sulabh Patel
 *   All rights reserved.
 */
#include "deck.h"
Deck::Deck() {
    reset();
}
void Deck::shuffle() {
    // Shuffling a stack directly is not straightforward since it's a LIFO list.
    // We need to temporarily store the elements in a vector to shuffle them.
    std::vector<Card> tempCards;
    while (!cards.empty()) {
        tempCards.push_back(cards.top());
        cards.pop();
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(tempCards.begin(), tempCards.end(), g);
    for (Card &card : tempCards) {
        cards.push(card);
    }
}
Card Deck::dealCard() {
    if(cards.empty()) {
        throw std::out_of_range("No more cards to deal.");
    }
    Card dealtCard = cards.top();
    cards.pop();
    return dealtCard;
}
void Deck::reset() {
    while (!cards.empty()) {
        cards.pop();
    }
    for (int suit = Card::HEARTS; suit <= Card::SPADES; ++suit) {
        for (int value = Card::TWO; value <= Card::NINE; ++value) {
            cards.push(Card(static_cast<Card::Suit>(suit),             
            static_cast<Card::Value>(value)));
        }
        cards.push(Card(static_cast<Card::Suit>(suit), Card::TEN));
        cards.push(Card(static_cast<Card::Suit>(suit), Card::JACK));
        cards.push(Card(static_cast<Card::Suit>(suit), Card::QUEEN));
        cards.push(Card(static_cast<Card::Suit>(suit), Card::KING));
        cards.push(Card(static_cast<Card::Suit>(suit), Card::ACE));
    }
}
