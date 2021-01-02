#ifndef _HAND_H
#define _HAND_H

#include "Card.h"

class Hand {

    public:
    Hand();
    ~Hand();
    /* Function to check if hand is empty
     * @return true if empty, false if not empty
     */
    bool isEmpty();
    /* Function to check if hand is full
     * @return true if full, false if not full
     */
    bool isFull();
    /* Function to get a Card at a specific position in the Hand
     * @param idx position of Card in Hand
     * @return Card object at position
     */
    Card getCard(int idx);
    /* Function to get the number of cards in Hand
     * @return number of cards in Hand
     */
    int size() const;
    /*
    * Function to add a card to Hand
    * @param Card card to be added to Hand
    * @return false if hand is full, else true
    */   
    bool addCard(Card& card);
    /* Function to remove card at a certain position in Hand
     * @param idx position of Card to be removed
     */
    void popCard(int idx);
    // Function to display Hand
    void display() const;
    /* Function to convert Hand to string for saving
     * @return string representation of Hand
     */
    std::string toString() const;
    /* Function to convert string representation of Hand into Hand object
     * @param gameStream input file stream containing string representation of Hand
     */
    void readIn(std::istream* gameStream);

    private:
    Card pile[5];
    int handSize;

};



#endif