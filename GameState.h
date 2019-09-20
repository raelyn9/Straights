#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "Subject.h"
#include "Player.h"
#include "Command.h"
#include <memory>
#include <vector>

struct State {
	int currentPlayer;
    int maxScore;
    bool roundDone;
    bool gameDone;
    bool isLegalPlay;
    bool showHistory;
    bool updatePlayer;
    std::string record;

    State(int currentPlayer, int maxScore, bool roundDone, bool gameDone, bool isLegalPlay, bool showHistory, bool updatePlayer, std::string record) : currentPlayer(currentPlayer), maxScore(maxScore),
            roundDone(roundDone), gameDone(gameDone), isLegalPlay(isLegalPlay), showHistory{showHistory},updatePlayer{updatePlayer},record{record} {}
};

class GameState : public Subject {
    private:
        int currentPlayer;
        int maxScore = 0;
        bool isLegalPlay = true;
        bool isGameDone = false;
        bool roundDone = false;
        bool showHistory = false;
        bool updatePlayer = false;
        std::string record;
        std::vector<std::shared_ptr<Player>> players;

        void setMaxScore();
        // Modifies: maxScore
        // Ensures: maxScore has the largest score out of the 4 players

        bool roundEnd();
        // Modifies: maxScore
        // Ensures: sets the maxScore so that it has the largest score and returns whether the round is over

        bool gameEnd();
        // Modifies: maxScore
        // Ensures: sets the maxScore so that it has the largest score and returns whether the game is over

    public:
        ~GameState();
        // Modifies: All member variables in GameState such that they are deleted
        // Ensures: GameState is deleted

        State getState();
        // Modifies: maxScore
        // Ensures: maxScore is set to the maximum score
        // Returns: An instance of the State struct such that it has the correct values to accurately represent the state of the game

        void setStartPlayer();
        // Modifies: currentPlayer
        // Ensures: currentPlayer is set to the index of the player who has 7S

        void setCurrentPlayer();
        // Modifies: currentPlayer
        // Ensures: currentPlayer is set to the index of the player who is currently playing

        int getCurrentPlayer() const;
        // Returns: The index corresponding to the player who is currently playing

        std::shared_ptr<Player> getPlayer(int num);
        // Require: the input integer is between 0 and 3
        // Returns: The player on the index specified by the input

        std::vector<int> getWinner() const; 
        // Ensures: A vector is created such that it has all of the players who won the game
        // Returns: A vector containing all of the players who won the game

        void setPlayers(std::vector<std::shared_ptr<Player>>& input);
        // Requires: input is populated with valid players
        // Modifies: players
        // Ensures: Players is populated with the players who are currently playing the game

        void setPlayer(std::shared_ptr<Player> p);
        // Requires: p (the player passed in) is valid
        // Modifies: Players
        // Ensures: The player passed in replaces the player in players which has the same player number

        void setLegalStatus(bool is);
        // Modifies: isLegalPlay
        // Ensures: isLegalPlay is set to the value passed in
        
        void playerTurn();
        // Modifies: isLegalPlay, roundDone
        // Ensures: isLegalPlay is set according to whether or not the player made a legal play
        //          roundDone is set according to whether or not the round has finished
        //          Determines what to do when it is a computer player's turn

        std::vector<int> getScores() const; 
        // Ensuress:: A vector containing the scores of all the players is returned
        // Returns: A vector containing all of the scores of the players

        void reset();
        // Modifies: maxScore, record
        // Ensures: maxScore is set to 0 (default state) and record is set to an empty string (default state)

        void addRecord(Type type, Card card);
        // Modifies: record
        // Ensures: record is updated such that it has the command type and card that were passed in for the current user

        std::string getRecord() const;
        // Returns: A string containing the record of moves made

        void setShowHistory(bool in);
        // Modifies: showHistory
        // Ensures: showHistory is assigned the value passed in

        void clearHistory();
        // Modifies: record
        // Ensures: record is set to its default state

        void setUpdatePlayer(bool in);
};

#endif