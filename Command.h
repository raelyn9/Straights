#ifndef COMMAND_H
#define COMMAND_H

#include "Card.h"
#include <istream>

enum Type { PLAY, DISCARD, DECK, QUIT, RAGEQUIT, BAD_COMMAND };

struct Command {
	Type type;
	Card card;
	
	Command() : type(BAD_COMMAND), card(SPADE, ACE) {}
	//Ensures: Initializes a commmand so that it has the type of BAD_COMMAND and the default card is the Ace of Spades
};

std::istream &operator>>(std::istream &, Command &);
//Requires: The user inputs a command which is in the expected format
//Modifies: istream, command
//Throws: Program terminates if there is a failure to get input or if the command is in the wrong format
//Ensures: The command passed in as a parameter is assigned the same values of the type and card (if the user inputs a card) that the user inputs
//Returns: The istream use for input

#endif
