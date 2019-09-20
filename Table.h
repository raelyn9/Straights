#ifndef TABLE_H
#define TABLE_H

#include "Card.h"
#include "Subject.h"
#include <map>
#include <vector>
#include <memory>
#include <algorithm>

struct tableState {
    std::shared_ptr<Card> lastCard;
    bool clearTable;
    tableState(std::shared_ptr<Card> lastCard, bool clearTable):  lastCard{lastCard}, clearTable{clearTable} {}
};

class Table: public Subject {
    private:
        std::map<Suit, std::shared_ptr<std::vector<std::shared_ptr<Card>>>> currCards;
        std::string ranks[RANK_COUNT] = {"A", "2", "3", "4", "5", "6",
		"7", "8", "9", "10", "J", "Q", "K"};
        std::shared_ptr<Card> lastCard;
        bool shouldClearTable = false;

    public:
        Table();
        //Ensures: initialize Table 

        bool checkLegalPlay(std::shared_ptr<Card>);
        // requires: card is not empty
        // ensures: check if the input card is legal play
        // returns: bool

        void addCard(Suit &suit, std::shared_ptr<Card> c);
        // requires: suit and c are not empty
        // ensures: input card is added to the currCards

        bool tableEmpty();
        // ensures: check if table has any card on it
        // returns: bool

        void clearTable();
        // ensures: all cards on table are cleared
        // modifies: currCards

        const std::vector<std::shared_ptr<Card>> getCards(Suit suit);
        // requires: suit is not empty
        // returns: all cards that belong to the input suit
        
        tableState getState() const;
        // ensures: get the status of the table
        // returns: tableState
        
    private:
        void initializeMap(); 
        // ensuresL initialize the map to hold a vector, add in the suits as keys in map 
        // modifies: currCards
};

#endif