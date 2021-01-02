#ifndef _SKIPBO_GAME_H
#define _SKIPBO_GAME_H

#include <string>
#include <vector>
#include "Player.h"
#include "DrawPile.h"
#include "FaceUpPile.h"
#include "BuildPile.h"

class SkipBoGame {

    public:
    //Constructors
    SkipBoGame();
    SkipBoGame(std::ifstream* gameStream);
    //destructor
    ~SkipBoGame();
    /* Function to convert deck file input stream to draw Pile object
     * @param stream deck file input stream
     */
    void setUpDraw(std::istream& stream);
    /* Function to iniitialize all players.
     * @param argv command line arguments containing number of players
    */
    void setUpPlayers(char **argv);
    // Function to display SkipBoGame
    void display() const;
    /* Function to convert SkipBoGame to string for saving
     * @return string representation of SkipBoGame
     */
    std::string toString() const;
    // Function to begin playing SkipBoGame
    void play();

    private:
    /*Function to deal cards to all players.
    * @param stockSize size of stock
    */
    void dealCards(int stockSize);
    // Function to play a player's turn
    void playTurn();
    // Function to check if a player has won
    bool GameOver();
    /* Function to check if a player's move is legal
    * @param moveFrom Location player wants to take Card from
    * @param moveTo Location player wants to move Card to
    * @return true if move is legal, false if move is illegal
    */
    bool legalMove(char moveFrom, char moveTo);
    /* Function to move a card from one location to another
    * @param moveFrom Location player wants to take Card from
    * @param moveTo Location player wants to move Card to
    */
    void makeMove(char moveFrom, char moveTo);
    /* Function to save SkipBoGame state in a file
    * @param filename name of file to save game to
    */
    void saveGame(std::string filename);
    // Function to fill a player's hand with Cards from the Draw
    void fillHand();
    /* Function to set aside a build pile that has been stacked to 12
    * @param i index of build pile to set aside
    */
    void setAside(int i);
    // Function to replenish Draw with cards from "set aside" Build piles
    void replenishDraw();

    //some instance variables
    //std::vector<Player*> players;
    DrawPile draw;
    // Array of build piles
    BuildPile build[4];
    // Vector of complete Build piles
    std::vector<BuildPile> aside;
    // Array of players
    Player* peep;
    //number of players
    int nump;
    //current player
    int curp;
    //current turn
    int turn = 0;
    // If turn = -1 this means a player won the game

    // Used to record shuffle status in save game function
    // Used to indicate if the Draw pile should be shuffled
    std::string shuffleOrNot = "";
};

#endif