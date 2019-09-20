#ifndef DECK_H
#define DECK_H

#include <memory>
#include <random>
#include <vector>
#include "Card.h"

static std::mt19937 rng;

class Deck {

private:
    int CARD_COUNT = 52; 
    int seed;
    std::vector<std::shared_ptr<Card>> cards;
    
public:
    Deck(int seed);
    //Ensures: Deck is initialized such that the correct number of cards are added to its vector, which represents the deck of cards

    void shuffle();
    //Requires: The user passes in a valid seed
    //Modifies: Cards
    //Ensures: The cards are shuffled according to the seed

    void createCards();
    //Modifies: Cards
    //Ensures: Cards is given the correct number of cards such that each card has a unique rank and suit combination and all combinations of ranks
    //         and suits are added to the deck

    std::shared_ptr<Card> getCards(int i) const; // return a shared pointer that points to a copy of the card
    //Ensures: A new shared pointer pointing to the card specified by the index is created
    //Returns: This new shared pointer is returned
};

#endif