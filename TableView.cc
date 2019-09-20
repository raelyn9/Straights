#include "TableView.h"
#include "Card.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
using namespace std;

TableView::TableView(std::shared_ptr<DeckView> deck): tableGrid{nullptr}, deckView{deck} {}

TableView::~TableView() {
	delete tableGrid;
	for (size_t i = 0; i < deckImages.size(); ++i) {
		delete deckImages.at(i);
	}
	table->detach(this);
}

void TableView::setTable(std::shared_ptr<Table> tbl){
	table = tbl;
	table->attach(this);
}

void TableView::buildTable(Glib::RefPtr<Gtk::Builder> & builder_) {
	builder_->get_widget("tableGrid", tableGrid);
	if (tableGrid == nullptr) {
		g_warning("unable to extract window sub-components"); 
		return;
    }
	
	Gtk::Image *card = nullptr;
	for (size_t i = 0; i < 52; ++i) {
		builder_->get_widget(std::to_string(i), card);
		card->set(deckView->null());
		deckImages.push_back(card);
	}
}

void TableView::notify() {
	tableState state = table->getState();
	std::shared_ptr<Card> card = state.lastCard;
	int index = deckView->getIndex(card->getRank(), card->getSuit());
	if (state.clearTable) {
		for (size_t i = 0; i < deckImages.size(); ++i) {
			Gtk::Image *cardImage = deckImages.at(i);
			cardImage->set(deckView->null()); // TODO: I feel like you can change this to just use the index
		}	
		return;
	}
	Gtk::Image *cardImage = deckImages.at(index);
	cardImage->set(deckView->image(card->getRank(), card->getSuit())); // TODO: I feel like you can change this to just use the index
}