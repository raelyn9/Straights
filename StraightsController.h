#ifndef STRAIGHTSCONTROLLER_H
#define STRAIGHTSCONTROLLER_H

#include "GameState.h"
#include "Player.h"
#include "Deck.h"
#include <assert.h>
#include <memory>

class StraightsController {

private:
    std::shared_ptr<Deck> deck;
    std::shared_ptr<Table> table;
    std::vector<std::shared_ptr<Player>> players;
    std::shared_ptr<GameState> gameState;
    int seed;

public:
    StraightsController(int seed);
    //Ensures: initialize StraightsController with the specified seed and its view
    
    void startGame(); 
    // Modifies: deck, table, players
    // Ensures: calls enterPlayers to create players for the game, shuffle the cards, and start the new Round
    //          Start the next round if no player has score that is higher than 80. 
    //          Print the winner and exist program if one player has score that is greater than 80

    void enterPlayers(std::vector<std::string>& input);
    //Modifies: players, ostream
    //Ensures: get player type from user, and create either HumanPlayer or ComputerPlayer according to the input

    void quitGame();
    // Ensures: The game ends

    std::shared_ptr<Table> getTable();
    // Returns: The table

    void playCard(int i);
    // Ensures: If player makes a legal play, the correct card is played and everything is updated
    //          If player tries to discard even though there are legal plays, output an error
    //          If the player discards, take appropriate action

    void newRound(); 
    //Ensures: a another round begins if no players' score is greater than 80

    void setCommand(Type type, Card card);
    // Ensures: The player's command is set according to the params

    std::vector<std::shared_ptr<Player>>& getPlayers();
    // Returns: a vector containing all of the players in the game

    std::shared_ptr<Player>& getPlayer(int num); 
    // Returns: The player stored in the index specificed by the param

    std::shared_ptr<GameState> getGameState() const;
    // Returns: The game state

    int getPlayerPoints(int num) const;
    // Returns: The points of the player associated with the index passed into the function

    int getPlayerDiscards(int num) const;
    // Returns: The number of discards of the player associated with the index passed into the function

    void rageQuit(int playerNum);
    // Modifies: players
    // Ensures: The player stored at the value passed in is changed so that it is a computer player
    
    void setSeed(int input);
    // Modifies: seed
    // Ensures: seed is set to the value passed into the function

    void clearGame(); 
    //Modifies: Player, Table 
    //Ensures: Clear all data from previous game

    void clearScores();
    //Modifies: score
    // Ensures: Each player's score is reset to its default value

private:
    void assignCards();
    //Modifies: cards that owned by players,ostream
    //Rnsures: assign the first 13 cards belong to Player 1, the next 13 cards belong to Player 2, the next 13 belong to Player 3, and the last 13 cards belong to Player 4
};


#endif