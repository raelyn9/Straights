#include "GameState.h"
#include "Command.h"
#include <iostream>
using namespace std;

GameState::~GameState() {}

void GameState::setMaxScore() { // determines the new max score
    for(int i = 0; i < players.size();i++){
        if (maxScore < players[i]->getScore()){
            maxScore = players[i]->getScore();
        }
    }
}

vector<int> GameState::getWinner() const { 
    int min = players[0]->getScore();
    vector<int> winner;
    winner.emplace_back(1);

    for(int i = 1; i < players.size();i++){
        if (min > players[i]->getScore()){
            min = players[i]->getScore();
            winner.clear();
            winner.emplace_back(i+1);
        } else if (min == players[i]->getScore()){
            winner.emplace_back(i+1);
        }
    }

    return winner;
}

void GameState::setStartPlayer() {
    for (size_t i = 0; i < players.size(); ++i) {
        if (players[i]->has7S()) {
            currentPlayer = i;
            break;
        }
    }
    playerTurn();
}

void GameState::playerTurn() {
    // Reset values in gameState for current player
    setLegalStatus(true);
    roundDone = roundEnd();

    // If the round ends, then notify observers and don't enter the logic for a player's turn
    if (roundDone) {
        Subject::notifyObservers();
        return;
    }

    // set all data needed for the current player (the legal plays, and the command to use)
    std::shared_ptr<Player> currPlayer = players.at(currentPlayer);
    currPlayer->setAllLegalPlays();
    currPlayer->determineCommand();
    addRecord(currPlayer->getCommand().type,currPlayer->getCommand().card);

    if (currPlayer->getCommand().type == Type::PLAY) {
        currPlayer->play();
        roundDone = false;
        Subject::notifyObservers();
        return setCurrentPlayer();  
    } else if (currPlayer->getCommand().type == Type::DISCARD) {
        currPlayer->discard();
        return setCurrentPlayer();
    } 
    Subject::notifyObservers();
}

void GameState::setCurrentPlayer() {
    if (currentPlayer == 3) {
        currentPlayer = 0;
    } else {
        ++currentPlayer;
    }
    playerTurn();
}

int GameState::getCurrentPlayer() const {
    return currentPlayer;
}

std::shared_ptr<Player> GameState::getPlayer(int num){
    return players[num];
}

bool GameState::roundEnd() {
    setMaxScore();
    for (size_t i = 0; i < players.size(); ++i) {
        if (players[i]->hasCards()) {
            return false;
        }
    }
    return true;
}

bool GameState::gameEnd() {
    return roundEnd() && maxScore > 80;
}

State GameState::getState() {
    State currState(currentPlayer, maxScore, roundDone, gameEnd() && roundEnd(), isLegalPlay, showHistory, updatePlayer, record);
    return currState;
}

void GameState::setPlayers(std::vector<std::shared_ptr<Player>>& input) {
    players = input;
}

void GameState::setLegalStatus(bool is) {
    isLegalPlay = is;
}

vector<int> GameState::getScores() const {
    vector<int> score;
    for(int i = 0; i < players.size();i++){
        score.emplace_back(players[i]->getScore());
    }
    return score;
}

void GameState::setPlayer(std::shared_ptr<Player> p) {
    players[currentPlayer] = p;
} 

void GameState::reset() {
    maxScore = 0;
    record = "";
}

void GameState::addRecord(Type type, Card card){
    if (type == BAD_COMMAND) {
        return;
    }

    string msg = "Player " + to_string(currentPlayer+1) + " "; 
    if (type == PLAY){
        msg += "plays ";
    } else {
        msg += "discards ";
    }
    msg += card.getValue();
    record += msg;
    record += "\n";
}

std::string GameState::getRecord() const {
    return record;
}

void GameState::setShowHistory(bool in) {
    showHistory = in;
}

void GameState::clearHistory(){
    record = "";
}

void GameState::setUpdatePlayer(bool in){
    updatePlayer = in;
}