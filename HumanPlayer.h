#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H
#include "Player.h"
#include "Card.h"
#include <set>
#include <memory>

class HumanPlayer: public Player{
public:
    HumanPlayer(std::shared_ptr<Table> table, int playerNum);
    //Ensures: Initialize HumanPlayer with a reference to the table and their player number

    void determineCommand() override;
    //Modifies: Command
    //Ensures: Command is set to its default values of BAD_COMMAND and AS respectively
};

#endif