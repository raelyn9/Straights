#include "StraightsController.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "Card.h"
#include "Table.h"
#include "Command.h"
#include <iostream> //TODO: remove

using namespace std;

StraightsController::StraightsController(int seed): seed{seed} {
    gameState = make_shared<GameState>();
    deck = make_shared<Deck>(seed);
    table = make_shared<Table>();
}

void StraightsController::newRound() {
    clearGame();
    deck->shuffle();
    assignCards();
    gameState->setStartPlayer();
}

void  StraightsController::assignCards() {
    for(int i = 0; i < players.size();i++) {
        for(int j = RANK_COUNT*(i) ; j < RANK_COUNT*(i+1); ++j){
            std::shared_ptr<Card> card = deck->getCards(j);
            players[i]->addCard(card);
        }
    }
}

void StraightsController::enterPlayers(std::vector<string>& input) { 
    players.clear();    
    for (int i = 0; i < input.size(); ++i){
        if (input[i] == "h"){
            players.emplace_back(make_shared<HumanPlayer>(table, i+1));
        } else if (input[i] == "c"){
            players.emplace_back(make_shared<ComputerPlayer>(table, i+1));
        } 
    }

    gameState->setPlayers(players);
}

void StraightsController::startGame() {
    deck = make_shared<Deck>(seed);
    clearScores();
    gameState->reset();

    newRound();
}

void StraightsController::clearScores() {
    for(int i = 0; i < players.size();i++){
        players[i]->clearScore();
    }
}


void StraightsController::clearGame() {
    for(int i = 0; i < players.size();i++){
        players[i]->clearCards();
    }
    table->clearTable();
    gameState->clearHistory();
}

void StraightsController::rageQuit(int playerNum){

    std::vector<std::shared_ptr<Card>> cards = players[playerNum]->getCards();
    std::vector<std::shared_ptr<Card>> discards = players[playerNum]->getDiscards();
    std::shared_ptr<Player> p = make_shared<ComputerPlayer>(cards, discards, table, playerNum + 1, players[playerNum]->getScore());
    
    gameState->setPlayer(p);
    players[playerNum] = p;
    gameState->playerTurn();
}

void StraightsController::quitGame() {
    exit(0);
}

std::shared_ptr<Table> StraightsController::getTable() {
    return table;
}

void StraightsController::playCard(int i) { //TODO: Should this be moved to gameState?
    int currPlayer = gameState->getCurrentPlayer();
    std::shared_ptr<Card> card= players[currPlayer]->getCard(i);
    bool playIsLegal = table->checkLegalPlay(card);
    
    if (playIsLegal) {
        players[currPlayer]->setCommand(Type::PLAY, *card);
        gameState->addRecord(Type::PLAY,*card);
        players[currPlayer]->play();
        gameState->setCurrentPlayer();
    } else if (!playIsLegal && players[currPlayer]->getNumOfAllLegalPlays() > 0) { // have a legal play but player played an illegal card
        // show dialog message
        gameState->setLegalStatus(false);
        gameState->notifyObservers();
        gameState->setLegalStatus(true);
    } else {
        players[currPlayer]->setCommand(Type::DISCARD, *card);
        gameState->addRecord(Type::DISCARD,*card);
        players[currPlayer]->discard();
        gameState->setCurrentPlayer();
    }    
    gameState->notifyObservers();
}

int StraightsController::getPlayerPoints(int num) const {
    return players[num]->getScore();
}

int StraightsController::getPlayerDiscards(int num) const {
    return players[num]->getNumDiscards();
}

std::vector<std::shared_ptr<Player>>&  StraightsController::getPlayers() {
    return players;
}

std::shared_ptr<Player>&  StraightsController::getPlayer(int num) {
    return players[num];
}

std::shared_ptr<GameState> StraightsController::getGameState() const {
    return gameState;
}

void StraightsController::setSeed(int input){
    seed = input;
}





