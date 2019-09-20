#ifndef INPUT_DIALOG_H
#define INPUT_DIALOG_H
#include <gtkmm.h>
#include <vector>
#include "StraightsController.h"


struct RadioGroup {
    Gtk::RadioButton * rb_1;
    Gtk::RadioButton * rb_2;

    ~RadioGroup() {
        delete rb_1;
        delete rb_2; 
    }
}

typedef RadioGroup;

class PlayerDialog: public Gtk::Dialog {
    Glib::RefPtr<Gtk::Builder> & builder;

    // Components of dialog
    Gtk::Button* doneBtn;    
    std::vector<std::shared_ptr<RadioGroup>> group;

    std::vector<std::string> result;
    std::shared_ptr<StraightsController> controller;

    void setDialog();
    // Modifies: doneBtn
    // Ensures: doneBtn is connected to the corresponding button in the playerDialog and the correct signal handler is connected to the button

    void setBtnGroups();
    // Modifies: group
    // Ensures: All radioButtons in playerDialog are added to the vector of buttons

    void doneClicked();
    // Ensures: Once the done button is clicked, the game commences and the players are set
public:
    PlayerDialog(BaseObjectType* cobject, Glib::RefPtr<Gtk::Builder>& inputbuilder);
    // Ensures: Initializes playerDialog such that it has the builder, controlle and baseObjectType passed in

    virtual ~PlayerDialog(); 
    // Modifies: All member variables
    // Ensures: Memory associated with playerDialog is properly cleaned up
    
    void setController(std::shared_ptr<StraightsController>& inputController);
    // Modifies: controller
    // Ensures: controller is set to the one passed into the function

    void setPlayer();
    // Modifies: result
    // Ensures: Each element in result corresponds to the value that the user inputs in the input dialog to indicate if a player is a computer or human
};        

#endif