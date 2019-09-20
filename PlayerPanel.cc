#include "PlayerPanel.h"
#include <iostream>
using namespace std;

PlayerPanel::PlayerPanel(int playerNum,Glib::RefPtr<Gtk::Builder> & builder):playerNum{playerNum}{
    buildPanel(builder);
}

PlayerPanel::~PlayerPanel() {
    delete rageQuit;
    delete point;
    delete discard;
    gameState->detach(this);
}

void PlayerPanel::setPanel(std::shared_ptr<StraightsController> inputController, std::shared_ptr<GameState> state){
    gameState = state;
    controller = inputController;
    gameState->attach(this);
}

void PlayerPanel::buildPanel(Glib::RefPtr<Gtk::Builder> & builder) {
    builder->get_widget( "player"+to_string(playerNum)+"Quit", rageQuit );
    builder->get_widget( "player"+to_string(playerNum)+"Points", point );
    builder->get_widget( "player"+to_string(playerNum)+"Discards", discard );
    rageQuit->signal_clicked().connect( sigc::mem_fun(*this, &PlayerPanel::rageQuitClicked) );
}

void PlayerPanel::checkActive(int curPlayer) {
    if (curPlayer != playerNum) {
        rageQuit->set_sensitive (false);
    } else {
        rageQuit->set_sensitive(true);
    }
}

void PlayerPanel::rageQuitClicked() const {
    controller->rageQuit(playerNum);
}

void PlayerPanel::updatePanel() {
    setPoints();
    setDiscards();
}

void PlayerPanel::setPoints() {
    int points = controller->getPlayerPoints(playerNum);
    point->set_text(to_string(points)+" points");
}

void PlayerPanel::setDiscards() {
    int discards = controller->getPlayerDiscards(playerNum);
    discard->set_text(to_string(discards)+" discards");
}

string PlayerPanel::getDiscards() {
    string msg;
    std::vector<std::shared_ptr<Card>> cards = gameState->getPlayer(playerNum)->getDiscards();
    for (size_t i=0; i<cards.size();i++){
        msg += " "+cards[i]->getValue();
    };
    return msg;
}

void PlayerPanel::notify() {

    // update the ragequit button so that it's active for the current user
    State state = gameState->getState();
    
    if(state.showHistory){
        return;
    }

    if (!state.roundDone){
        checkActive(state.currentPlayer);
    } else {
        checkActive(-1);
    }
    
    // update current points & discards
    updatePanel();
}