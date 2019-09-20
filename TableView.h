#ifndef TABLE_VIEW_H
#define TABLE_VIEW_H
#include "Card.h"
#include "Observer.h"
#include "Table.h"
#include "DeckView.h"
#include <gtkmm.h>
#include <vector>

class TableView: public Observer {
    Gtk::Grid *tableGrid;
    std::vector<Gtk::Image*> deckImages;
    std::shared_ptr<Table> table;
    std::shared_ptr<DeckView> deckView;

    public: 
        TableView(std::shared_ptr<DeckView> deck);
        // Ensures: initialize TableView
        
        ~TableView();
        // Modifies: all member variables
        // Ensures: Memory is cleaned up properly and it detaches itself from the subjects it is observing 

        void setTable(std::shared_ptr<Table> table);
        // Requires: the shared pointer that points at table is not null
        // Modifies: table
        // Ensures: set the value of the table that that TableView is observing

        void buildTable(Glib::RefPtr<Gtk::Builder> & builder_);
        // Requires: the Glib builder is not null
        // Modifies: tableGrid, deckImages, deckView
        // Ensures: build the tableview and initialize it with empty card images 

        void notify() override;
        // Ensures: get the current state of the table and show its content in the view
        // Modifies: deckImages, deckView
};

#endif