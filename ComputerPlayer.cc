#include "ComputerPlayer.h"
#include "Command.h"
#include "Card.h"
#include "vector"
#include "Table.h"
#include <iostream>

ComputerPlayer::ComputerPlayer(std::shared_ptr<Table> table, int playerNum): Player(table, playerNum) {}

ComputerPlayer::~ComputerPlayer() {}

// Used to create a new Computer player when human player ragequits by taking its cards, discards, and playerNum
ComputerPlayer::ComputerPlayer(std::vector<std::shared_ptr<Card>> cards, std::vector<std::shared_ptr<Card>> discards, std::shared_ptr<Table> table, int playerNum, int score): Player(cards, discards, table, playerNum, score) {}

void ComputerPlayer::determineCommand() {
    if (getNumOfAllLegalPlays() > 0) { // have a legal play
        setCommand(PLAY, getFirstLegalPlay());
    } else { // don't have any legal plays so need to discard cards
        setCommand(DISCARD, getFirstCard());
    }
}

