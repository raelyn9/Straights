#include "Deck.h"
#include "Card.h"
#include <iostream>

using namespace std;

Deck::Deck(int seed):seed{seed} {
    createCards(); // adds the correct number of cards into the deck with the appropriate suit and rank
    rng.seed(seed);
}

void Deck::shuffle() {
	int n = CARD_COUNT;
	while ( n > 1 ) {
		int k = (int) (rng() % n);
		--n;
		cards[n].swap(cards[k]);
	}
}

void Deck::createCards() { 
    for(int i = 0 ; i < SUIT_COUNT; i++){ // add the cards into the vector of cards
        for(int j = 0 ; j < RANK_COUNT; j++){
    		cards.emplace_back(make_shared<Card>(Suit(i), Rank(j)));
        }
    }
}

std::shared_ptr<Card> Deck::getCards(int i) const { // returns the card in the deck at the specified index
    std::shared_ptr<Card> card = make_shared<Card>(cards[i]->getSuit(),cards[i]->getRank());
    return card;
}
