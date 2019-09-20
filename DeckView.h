#ifndef DECK_VIEW_H
#define DECK_VIEW_H
#include "Card.h"
#include <vector>
#include <gtkmm.h>
#include <gdkmm/pixbuf.h>

class DeckView {
    std::vector<Glib::RefPtr< Gdk::Pixbuf>> deck; // Contains the pixel buffer images.

    public:
        DeckView();
        //Ensures: DeckView is instantiated correctly

        Glib::RefPtr<Gdk::Pixbuf> image(Rank f, Suit s) const;
        // Requires: The rank and suit passed in are valid
        // Returns: The image for the specified card

        Glib::RefPtr<Gdk::Pixbuf> null() const;                 
        // Returns: The image to use for the blank cards

        int getIndex(Rank r, Suit s) const;
        // Requires: The rank and suit passed in are valid
        // Returns: The index corresponding to the element where the card specified is stored in the vector
};

#endif