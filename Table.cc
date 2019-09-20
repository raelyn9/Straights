#include "Table.h"
#include "Card.h"

#include <iostream>
#include <vector>

using namespace std;

Table::Table(): lastCard{make_shared<Card>(Suit::SPADE, Rank::SEVEN)} {
    initializeMap();
}

void Table::clearTable() {

    for (auto it = currCards.begin(); it != currCards.end(); ++it){
        it->second.reset();
    }

    initializeMap();
    shouldClearTable = true;
    Subject::notifyObservers();
}

void Table::initializeMap(){
    currCards[Suit::SPADE] = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    currCards[Suit::CLUB] = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    currCards[Suit::DIAMOND] = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    currCards[Suit::HEART] = std::make_shared<std::vector<std::shared_ptr<Card>>>();
}

bool Table::checkLegalPlay(std::shared_ptr<Card> card) {
    Suit suit = card->getSuit();
    Rank rank = card->getRank();

    if (card->getRank() == Rank::SEVEN) {
        return true; 
    }

    for (size_t i = 0; i < currCards[suit]->size(); ++i) {
        if (currCards[suit]->at(i)->getRank() == rank + 1 || currCards[suit]->at(i)->getRank() == rank - 1) {
            return true;
        }
    }
    return false;
}

void Table::addCard(Suit &suit, std::shared_ptr<Card> c) {
    shouldClearTable = false;
    currCards[suit]->emplace_back(c);

    std::sort( currCards[suit]->begin( ), currCards[suit]->end( ), [ ]( const std::shared_ptr<Card>& lhs, const std::shared_ptr<Card>& rhs ) {
        return lhs->getRank() < rhs->getRank();
    });

    lastCard = c;
    Subject::notifyObservers();
}

bool Table::tableEmpty() {
    return currCards[Suit::CLUB]->size() == 0 && currCards[Suit::DIAMOND]->size() == 0 && currCards[Suit::HEART]->size() == 0 && currCards[Suit::SPADE]->size() == 0;
}

const std::vector<std::shared_ptr<Card>> Table::getCards(Suit suit) {
    return *currCards[suit]; 
}

tableState Table::getState() const {
    return tableState(lastCard, shouldClearTable);
}