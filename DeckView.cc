#include "DeckView.h"
#include "Card.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>

using std::string;
using std::transform;

// Sets up an array of the Portable Network Graphics (PNG) file names that contain the necessary card images.
// The deck will load the contents into pixel buffers for later use.
const char * image_names[] = {
    // Cards for Club
	"cards/0_0.png", "cards/0_1.png", "cards/0_2.png", "cards/0_3.png", "cards/0_4.png", "cards/0_5.png", "cards/0_6.png", "cards/0_7.png", "cards/0_8.png", "cards/0_9.png", "cards/0_j.png", "cards/0_q.png", "cards/0_k.png", 
    // Cards for Diamond
	"cards/1_0.png", "cards/1_1.png", "cards/1_2.png", "cards/1_3.png", "cards/1_4.png", "cards/1_5.png", "cards/1_6.png", "cards/1_7.png", "cards/1_8.png", "cards/1_9.png", "cards/1_j.png", "cards/1_q.png", "cards/1_k.png", 
	// Cards for Hearts
	"cards/2_0.png", "cards/2_1.png", "cards/2_2.png", "cards/2_3.png", "cards/2_4.png", "cards/2_5.png", "cards/2_6.png", "cards/2_7.png", "cards/2_8.png", "cards/2_9.png", "cards/2_j.png", "cards/2_q.png", "cards/2_k.png", 
	// Cards for Spades
	"cards/3_0.png", "cards/3_1.png", "cards/3_2.png", "cards/3_3.png", "cards/3_4.png", "cards/3_5.png", "cards/3_6.png", "cards/3_7.png", "cards/3_8.png", "cards/3_9.png", "cards/3_j.png", "cards/3_q.png", "cards/3_k.png", 
	// Blank card
	"cards/nothing.png"
};

// Loads the image from the specified file name into a pixel buffer.
Glib::RefPtr<Gdk::Pixbuf> createPixbuf(const string & name) {
	return Gdk::Pixbuf::create_from_file( name );
}

// Returns the image for the specified card.
Glib::RefPtr<Gdk::Pixbuf> DeckView::image(Rank r, Suit s) const {
	int index = ((int) s)*13 + ((int) r );
	return deck.at(index);
} 

// Returns the image to use for the placeholder.
Glib::RefPtr<Gdk::Pixbuf> DeckView::null() const {
	return deck.at(deck.size()- 1);
}

// Get the corresponding index in the array for the given image
int DeckView::getIndex(Rank r, Suit s) const {
	return ((int) s)*13 + ((int) r );
}

// Create the deck
DeckView::DeckView() {
	transform( &image_names[0], &image_names[G_N_ELEMENTS(image_names)], std::back_inserter(deck), &createPixbuf);
}
