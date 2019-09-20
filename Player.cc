#include "Player.h"
#include "Card.h"
#include <iostream>
using namespace std;

Player::Player(std::shared_ptr<Table> table,int playerNum): table{table}, playerNum{playerNum} {}

Player::Player(std::vector<std::shared_ptr<Card>> cards, std::vector<std::shared_ptr<Card>> discards, std::shared_ptr<Table> table, int playerNum, int score): cards{cards}, discards{discards}, table{table}, playerNum{playerNum},score{score} {}

Player::~Player() {}

void Player::play() {
    int index = findCard(command.card);
    Suit suit = command.card.getSuit();
    table->addCard(suit, cards.at(index)); // add card to pile of cards which were already played
    cards.erase(cards.begin() + index); // remove card from player's hand
}

void Player::discard() {
    int index = findCard(command.card);

    // add to score
    score += cards.at(index)->getRank() + 1;

    discards.push_back(std::move(cards.at(index))); // adds card to player's discarded pile
    cards.erase(cards.begin() + index); // removes card from player's hand
    Subject::notifyObservers();
}

void Player::addCard(std::shared_ptr<Card>& input){
    cards.emplace_back(input);
}

bool Player::has7S() const {
    for (int i = 0; i < cards.size();i++){
        if (cards[i]->getRank() == SEVEN && cards[i]->getSuit() == SPADE){
            return true;
        }
    }
    return false;
}

bool Player::hasCards () const {
    return cards.size() != 0;
} 

void Player::clearCards() {
    cards.clear();
    discards.clear();
}

int Player::getScore() const {
    return score;
}

int Player::findCard(Card card) const {
    for (size_t i = 0; i < cards.size(); ++i) { // returns index of card that was passed in
        if (*cards.at(i) == command.card) {
            return i;
        }
    }
    return -1;
}

Command Player::getCommand() const {
    return command;
}

void Player::setCommand(Type type, Card card)  {
    command.type = type;
    command.card = card;
}

std::vector<std::shared_ptr<Card>> Player::getCards() {
    return cards;
}

std::vector<std::shared_ptr<Card>> Player::getDiscards(){
    return discards;
}

void Player::setAllLegalPlays() {
    allLegalPlays.clear(); // removes all the legal plays from before

    if (table->tableEmpty()) { // if the table is empty, then the only legal play is 7S        
        for (int i = 0; i < cards.size();i++){
            if (cards[i]->getRank() == SEVEN && cards[i]->getSuit() == SPADE){
                allLegalPlays.push_back(cards.at(i));
                return;
            }
        }
    }

    for (size_t i = 0; i < cards.size(); ++i) {  // check for possible legal plays and add them to the allLegalPlays vector
        if (table->checkLegalPlay(cards.at(i))) {
            allLegalPlays.push_back(cards.at(i));
        }
    }
}

size_t Player::getNumOfAllLegalPlays() const {
    return allLegalPlays.size();
}

Card Player::getFirstCard() const {
    return *cards[0];
}

Card Player::getFirstLegalPlay() const {
    return *allLegalPlays[0];
}

const std::vector<std::shared_ptr<Card>> Player::getAllLegalPlays() const {
    return allLegalPlays;
}

const std::shared_ptr<Table> Player::getTable() const {
    return table;
}

std::shared_ptr<Card> Player::getCard(int i) const {
    return cards.at(i);
}    
    
int Player::getNumDiscards() const {
    return discards.size();
}

int Player::getNumCards() const {
    return cards.size();
}

void Player::clearScore() {
    score = 0;
}