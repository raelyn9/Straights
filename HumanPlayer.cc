#include "HumanPlayer.h"
#include "Deck.h"
#include "Card.h"
#include <iostream>
using namespace std;

HumanPlayer::HumanPlayer(std::shared_ptr<Table> table, int playerNum): Player(table, playerNum) {}

void HumanPlayer::determineCommand() {
    setCommand(Type::BAD_COMMAND, Card(SPADE, ACE));
}