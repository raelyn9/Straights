#ifndef HEADER_VIEW_H
#define HEADER_VIEW_H

#include "StraightsController.h"
#include <gtkmm.h>
#include <vector>

class HeaderView {
    // Components making up the Header
    Gtk::Button *startButton;
    Gtk::Button *endButton;
    Gtk::TextView *seedText;

    std::shared_ptr<StraightsController> controller;

    void startButtonClicked();	
    // Requires: User inputs a valid seed
    // Ensures: Seed is set properly and game starts when user presses the "start" button

    void endButtonClicked();
    // Ensures: When user presses the "end" button, the game is finished
    
public:
    HeaderView();
    // Ensures: HeaderView is initialized such that it has the controller which is passed in

    ~HeaderView();
    // Modifies: startButton, endButton, seedText
    // Ensures: They are properly deleted

    void setHeader(std::shared_ptr<StraightsController> controller);
    // Modifies: controller
    // Ensures: controller is set to the controller input into the function
    
    void buildHeader(Glib::RefPtr<Gtk::Builder> & builder_);
    // Modifies: startButton, endButton, seedText
    // Ensures: HeaderView is initialized such that all the components are set and buttons are linked with the correct handler
};

#endif