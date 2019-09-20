#ifndef WINDOW_H
#define WINDOW_H
#include <gtkmm.h>
#include "PlayerPanel.h"
#include "PlayerHandPanel.h"
#include "TableView.h"
#include "PlayerDialog.h"
#include "Observer.h"
#include "Player.h"

#include <vector>
#include <memory>

class GameWindow: public Gtk::Window, Observer {
    private: 
        Glib::RefPtr<Gtk::Builder> & builder_;
        Glib::RefPtr<Gio::SimpleActionGroup> actionGroup_;
        std::shared_ptr<TableView> tableView; 
        std::shared_ptr<DeckView> deckView;
        std::shared_ptr<PlayerHandPanel> hand;
        std::vector<std::shared_ptr<PlayerPanel>> playerPanels;
        std::shared_ptr<StraightsController> controller;
        PlayerDialog* inputDialog = nullptr;
        std::shared_ptr<GameState> gameState;

        // Components making up the Header
        Gtk::Button *startButton;
        Gtk::Button *endButton;
        Gtk::TextView *seedText;

        void startButtonClicked();	
        // Requires: User inputs a valid seed
        // Ensures: Seed is set properly and game starts when user presses the "start" button

        void endButtonClicked();
        // Ensures: When user presses the "end" button, the game is finished

    public:
        GameWindow(BaseObjectType *, Glib::RefPtr<Gtk::Builder> &);
        // Ensures: GameWindow is initialized suc hthat it has the builder, application, and controller passed in

        ~GameWindow();         
        // Modifies: all member variables
        // Ensures: Memory is cleaned up properly and it detaches itself from the subjects it is observing 

        void notify() override;
        // Ensures: Shows the appropriate dialog depending on the state of the game

        void setController(std::shared_ptr<StraightsController>& inputController);  
        // Requires: Valid controller is passed in
        // Modifies: controller
        // Ensures: the controller is set to the controller passed into the function

        void setGame();    
        // Ensures: The game begins by starting a new round

        void setDialog();  
        // Modifies: inputDialog
        // Ensures: inputDialog is initialized and attached to the corresponding dialog
        //          (inputDialog is used to allow the user to input whether players are computer or human)

        void showMesageDialog(std::string str);
        // Ensures: A new dialog is created such that the specified text is shown

        void setHeader(std::shared_ptr<StraightsController> controller);
        void buildHeader(Glib::RefPtr<Gtk::Builder> & builder_);
        // Modifies: startButton, endButton, seedText
        // Ensures: HeaderView is initialized such that all the components are set and buttons are linked with the correct handler
};

#endif