#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H
#include "Player.h"

#include <memory>

class ComputerPlayer: public Player {
public:
    ComputerPlayer(std::shared_ptr<Table> table, int playerNum);
    //Ensures: Computer player is initialized such that it has a shared_ptr to the table and playerNum which were passed in

    ~ComputerPlayer();
    //Ensures: Cleans up data specific to computerPlayer

    ComputerPlayer(std::vector<std::shared_ptr<Card>> cards, std::vector<std::shared_ptr<Card>> discards, std::shared_ptr<Table> table, int playerNum, int score);
    //Ensures: ComputerPlayer is initalized with existing data (their hand, discarded cards, player number, and table) from HumanPlayer when a HumanPlayer ragequits

    void determineCommand() override;
    //Requires: A valid view is passed in
    //Modifies: Command
    //Ensures: Command is given a type which corresponds to the next move to be made by the player and it is also given the card associated with that move
};

#endif