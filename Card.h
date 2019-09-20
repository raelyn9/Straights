#ifndef CARD_H
#define CARD_H

#include <ostream>
#include <istream>

enum Suit { CLUB, DIAMOND, HEART, SPADE, SUIT_COUNT };
enum Rank { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN,
			EIGHT, NINE, TEN, JACK, QUEEN, KING, RANK_COUNT };

class Card {
	friend std::istream &operator>>(std::istream &, Card &);

public:
	Card(Suit, Rank);
	// Ensures: Initializes a Card so that its suit and rank is equal to that of the Suit and Rank which were passed in

	Suit getSuit() const;
	//Returns: The card's suit

	Rank getRank() const;
	//Returns:  The card's rank

	std::string getValue() const;
	
private:
	Suit suit_;
	Rank rank_;
};

bool operator==(const Card &, const Card &);
//Requires: Both cards which are passed in are valid cards
//Returns: Whether or not the cards have the same rank and suit

std::ostream &operator<<(std::ostream &, const Card &);
//Requires: The card that is passed in is valid
//Modifies: The ostream
//Ensures: The card is output in the format <rank><suit>
//Returns: The ostream object which was used to output the card

std::istream &operator>>(std::istream &in, Card &c);
//Requires: The user inputs a card which is correctly formatted
//Modifies: The card that is passed in
//Throws: Program will terminate if there is an invalid rank, if the user inputs a 10 and the second character 
//        is not a 0, or if there is an invalid suit
//Ensures: The card that is passed in so that it has the Rank and Suit which were input by the user
//Returns: The istream object which was used for input
#endif
