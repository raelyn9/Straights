#ifndef PLAYER_HAND_PANEL_H
#define PLAYER_HAND_PANEL_H
#include "StraightsController.h"
#include "DeckView.h"
#include "Observer.h"
#include "GameState.h"
#include <gtkmm.h>
#include <vector>

class PlayerHandPanel: public Observer {
    std::vector<Gtk::Button*> buttonList;
    std::shared_ptr<StraightsController> controller;
    std::shared_ptr<DeckView> deckView;
    std::shared_ptr<GameState> gameState;
    Gtk::Label* hint;
    Gtk::Button* showRecord;

    void clicked(int i);
    // Ensures: When player clicks a button that has a card on it, the correct action is taken

    void setHint(std::vector<std::shared_ptr<Card>> cards);
    // Ensures: A string containing the hints for the current player is generated and displayed

    void recordClicked();
    // Ensures: The record of the player's history is showed 

public:
    PlayerHandPanel(std::shared_ptr<DeckView> deck);
    // Ensures: PlayerHandPanel is initialized such that it has the deck which is passed in

    void buildPanel(Glib::RefPtr<Gtk::Builder> & builder);
    // Ensures: Panel is set such that it has all of the buttons and labels on the corresponding panel and links the signal handler to the correct button

    ~PlayerHandPanel();
    // Modifies: All member variables
    // Ensures: Memory is cleaned up properly

    void setHand(std::shared_ptr<GameState> gameState, std::shared_ptr<StraightsController> controller);
    // Modifies: gameState and controller
    // Ensures: gameState and controller are set to the values passed in

    void notify();
    // Modifies: buttonList
    // Ensures: The buttons are set so that they either have the image of a card or "nothing" depending on the current player's hand    
};


#endif
