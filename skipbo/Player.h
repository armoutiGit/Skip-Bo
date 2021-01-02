#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include "DrawPile.h"
#include "FaceUpPile.h"
#include "Hand.h"


class Player {

    public:
    Player();
    ~Player();
    // Function to display Player
    void display() const;
    /* Function to convert Player to string for saving
     * @return string representation of Player
     */
    std::string toString() const;
    /* Function to convert string representation of Player into Player object
     * @param is input file stream containing string representation of Player
     */
    void readIn(std::istream* gameStream);

    private:
    friend class SkipBoGame; //to initialize the players variables below
    
    std::string name;
    FaceUpPile discard[4];
    FaceUpPile stock;
    Hand hand;

};

#endif