#include "PlayerDialog.h"
#include "GameWindow.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
using namespace std;


PlayerDialog::PlayerDialog( BaseObjectType* cobject,  Glib::RefPtr<Gtk::Builder>& inputbuilder): 
						Gtk::Dialog{cobject}, builder{inputbuilder} {

	set_default_size( 600, 600 );
	set_border_width( 10 );

	setDialog();
    setBtnGroups();
}


PlayerDialog::~PlayerDialog() {
    delete doneBtn;
}

void PlayerDialog::setController(std::shared_ptr<StraightsController>& inputController){
    controller = inputController;
}

void PlayerDialog::setDialog(){
    builder->get_widget("doneBtn", doneBtn );
    doneBtn->signal_clicked().connect( sigc::mem_fun(*this, &PlayerDialog::doneClicked) );
}

void PlayerDialog::setBtnGroups(){
    for (int i=0; i<4; i++) {
        shared_ptr<RadioGroup> grp = make_shared<RadioGroup>();
        builder->get_widget("radiobutton"+to_string(i)+"1", grp->rb_1 );
        builder->get_widget("radiobutton"+to_string(i)+"2", grp->rb_2 );
        
        group.push_back(grp);
    }
}

void PlayerDialog::setPlayer() {
    result.clear();
    for(size_t i=0; i < group.size(); ++i){
        if (group[i]->rb_1->get_active()) {
            result.emplace_back("h");
        } else {
            result.emplace_back("c");
        }
    }
    controller->enterPlayers(result);   
}


void PlayerDialog::doneClicked() {
    setPlayer();
    this->hide();
}