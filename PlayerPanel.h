#ifndef PLAYER_PANEL_H
#define PLAYER_PANEL_H
#include <gtkmm.h>
#include "StraightsController.h"
#include "Player.h"
#include "Observer.h"


class PlayerPanel: public Observer {
    // Components of panel
    Gtk::Button* rageQuit;
    Gtk::Label* point;
    Gtk::Label* discard;

    // subjects
    std::shared_ptr<GameState> gameState;

    int playerNum;
    std::shared_ptr<StraightsController> controller;

    void rageQuitClicked() const;
    // Ensures: When rageQuit is clicked, the correct action is taken

    void setPoints();
    // Modifies: points
    // Ensures: The points label is updated to show the player's current points

    void setDiscards();
    // Modifies: discards
    // Ensures: The discards label is updated to show the player's current number of discards

    void updatePanel();
    // Modifies: points, discards and rageQuit
    // Ensures: The panel is updated to show the correct points, number of discards and disable/enable the rageQuit button as appropriate

    void checkActive(int curPlayer);
    // Modifies: ragequit
    // Ensures: rageQuit is disable/enabled depending on the current player
public:
    PlayerPanel(int playerNum,Glib::RefPtr<Gtk::Builder> & builder);
    // Ensures: Initializes the PlayerPanel so that it has the playerNum and builder passed in

    ~PlayerPanel();

    void notify() override; 
    // Modifies: points, discards and ragequit
    // Ensures: The panel is updated to reflect the data of each of the players

    std::string getDiscards(); 
    // Returns: Get the string representation of all of the player's discarded cards

    void setPanel(std::shared_ptr<StraightsController> inputController, std::shared_ptr<GameState> gameState);
    // Modifies: player, gameState, controller 
    // Ensures: player, gameState and controller are set to the params 

    void buildPanel(Glib::RefPtr<Gtk::Builder> & builder);
    // Modifies: rageQuit, point, discard
    // Ensures: The components are set to their counterparts in the GUI and the correct handler is attached to each button

};



#endif