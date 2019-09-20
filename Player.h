#ifndef PLAYER_H
#define PLAYER_H
#include "Card.h"
#include "Table.h"
#include "Command.h"
#include "Subject.h"
#include <vector>
#include <memory>

class Player: public Subject {
private:
    int score = 0;
    std::vector<std::shared_ptr<Card>> discards; // player's pile of discarded cards
    std::vector<std::shared_ptr<Card>> cards; 
    std::vector<std::shared_ptr<Card>> allLegalPlays; // legal plays for player
    std::shared_ptr<Table> table;
    Command command;
    int playerNum;

    int findCard(Card c) const;
    // Requires: The card exists in the player's hand
    // Returns: The index of the card passed in

public:
    Player(std::shared_ptr<Table> table, int playerNum);
    // Ensures: Initializes player with the table and playerNum passed in

    virtual ~Player() = 0;
    // Modifies: All member variables
    // Ensures: Player is properly cleaned up and memory is deallocated

    Player(std::vector<std::shared_ptr<Card>> cards, std::vector<std::shared_ptr<Card>> discards, std::shared_ptr<Table> table, int playerNum, int score);
    // Ensures: Initializes player with the cards, discards, table and playerNum passed in. Is used for when a human player quits so that the 
    //         computer play can take the human player's data
    
    void play();
    // Requires: The card that is to be played is valid and exists in cards
    // Modifies: Table, cards
    // Ensures: The card is added to Table such that it is in the appropriate grouping for suits, and the card is removed from cards
    
    void discard();
    // Requires: The card to be discarded is valid and exists in cards
    // Modifies: Cards, discards
    // Ensures: The card is removed from cards and the card is added into the player's discarded cards pile

    bool has7S() const; 
    // Returns: A bool indicating whether or not the player has the card 7S

    bool hasCards () const; 
    // Returns: A bool indicating whether or not the player has any cards left

    void clearCards();
    // Modifies: Cards, discards
    // Ensures: All cards are removed from the cards so that the player has an empty hand. All cards are removed from discards so 
    //         the player's discard pile is empty

    void addCard(std::shared_ptr<Card>& input);
    // Requires: A valid card is passed in
    // Modifies: Cards
    // Ensures: The card passed in is added to cards

    int getScore() const; 
    // Returns: player's score

    std::vector<std::shared_ptr<Card>> getCards();
    // Returns: vector of shared pointers that point to cards in cards that the player has

    std::vector<std::shared_ptr<Card>> getDiscards();
    // Returns: vector of shared pointers that point to the cards in the player's discarded pile

    Command getCommand() const;
    // Returns: The current values of the player's command

    void setAllLegalPlays();
    // Modifies: allLegalPlays
    // Ensures: all cards in allLegaPlays from player's previous turn are removed and the new legal plays for the player are added to the vector

    size_t getNumOfAllLegalPlays() const;
    // Returns: Size of vector of the legal play cards 

    void setCommand(Type type, Card card);
    // Requires: The type and card which are passed in are valid
    // Modifies: command
    // Ensures: Command is assigned the type and card which were passed into the function

    Card getFirstCard() const;
    // Returns: The first card in the player's cards

    Card getFirstLegalPlay() const;
    // Returns: The first card that the player can legally play

    const std::vector<std::shared_ptr<Card>> getAllLegalPlays() const;
    // Returns: the vector containing all of the player's cards which can be legall playe

    virtual void determineCommand() = 0;
    // Modifies: Command
    // Ensures: Command is given the correct type and card 

    const std::shared_ptr<Table> getTable() const;
    // Returns: A pointer to the table

    std::shared_ptr<Card> getCard(int i) const;
    // Returns: A pointer to the card specified by the index
    // Throws: Out_of_bounds exception if the index is not valid

    int getNumDiscards() const;
    // Returns: The number of discarded cards

    int getNumCards() const;
    // Returns: The number of cards in the player's hand

    void clearScore();
    // Modifies: score
    // Ensures: score is set to a default value of 0
};
#endif