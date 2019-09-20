#include "PlayerHandPanel.h"
#include <gtkmm.h>
#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std;

PlayerHandPanel::PlayerHandPanel(std::shared_ptr<DeckView> deck): deckView{deck}{}

PlayerHandPanel::~PlayerHandPanel() {
    for (size_t i = 0; i < buttonList.size(); ++i) {
        delete buttonList.at(i);
    }
    delete showRecord;
    delete hint;
    gameState->detach(this);
}

void PlayerHandPanel::setHand(std::shared_ptr<GameState> state, std::shared_ptr<StraightsController> inputcontroller){
    gameState = state;
    controller = inputcontroller;
    gameState->attach(this);
}

void PlayerHandPanel::clicked(int i) {
    controller->playCard(i);
}

void PlayerHandPanel::buildPanel(Glib::RefPtr<Gtk::Builder> & builder) {
    Gtk::Button *button = nullptr;
    for (size_t i = 0; i < 13; ++i) {
        Gtk::Image *image = new Gtk::Image(deckView->null()); // todo: change this so that it has the proper cards
        builder->get_widget("c"+to_string(i), button);
        button->set_image(*image);
        button->signal_clicked().connect(sigc::bind<int>( sigc::mem_fun(*this, &PlayerHandPanel::clicked), i) );
        buttonList.push_back(button);
    }
    builder->get_widget( "hintLabel", hint);
    builder->get_widget( "showRecord", showRecord);
    showRecord->signal_clicked().connect( sigc::mem_fun(*this, &PlayerHandPanel::recordClicked) );
}

void PlayerHandPanel::notify() {
    State state = gameState->getState();
    if (state.showHistory) {
        return;
    }

    std::shared_ptr<Player> currPlayer = controller->getPlayer(state.currentPlayer);  
    setHint(currPlayer->getAllLegalPlays());

    // set the buttons to show the player's cards
    for (size_t i = 0; i < currPlayer->getNumCards(); ++i) {
        std::shared_ptr<Card> card = currPlayer->getCard(i);
        Gtk::Image *image = new Gtk::Image(deckView->image(card->getRank(), card->getSuit()));
        buttonList.at(i)->set_image(*image);
        buttonList.at(i)->set_sensitive(true);
    }

    // set the buttons to null for the cards that the player has already played
    for (size_t i = currPlayer->getNumCards(); i < buttonList.size(); ++i) {
        Gtk::Image *image = new Gtk::Image(deckView->null());
        buttonList.at(i)->set_image(*image);
        buttonList.at(i)->set_sensitive(false);
    }
}

void PlayerHandPanel::setHint(std::vector<std::shared_ptr<Card>> cards){
    string str = "Hints:";
    for (size_t i=0; i<cards.size(); i++){
        str += " "+ cards[i]->getValue();
    }
    hint->set_text(str);
}

void PlayerHandPanel::recordClicked() {
    gameState->setShowHistory(true);
    gameState->notifyObservers();
}