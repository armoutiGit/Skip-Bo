#ifndef _PILE_H
#define _PILE_H

#include <algorithm>
#include <vector>
#include <iostream>
#include "Card.h"

class Pile {
  
  protected:
  std::vector<Card> pile;
  
  //bool shuffle;

  public:
  Pile() { }

  virtual ~Pile() { }

  /* Function to return size of Pile
   * @return size of pile
   */
  int size() const { return pile.size(); }
  /* Function to check if Pile is empty
   * @return true if empty, false if not empty
   */
  bool isEmpty();
  /* Function to add card to top of Pile
   * @param c Card to add
   */
  virtual void addCard(Card& c) { pile.push_back(c); }
  // Function to remove top Card from Pile
  void popCard();
  // Function to remove all Cards from Pile
  void clear() { pile.clear(); }
  /* Function to convert Pile to string for saving
   * @return string representation of Pile
   */
  std::string toString() const;  // for saving state
  /* Function to convert string representation of Pile into Pile object
   * @param is input file stream containing string representation of Pile
   */
  void readIn(std::istream* is);  // students to write this, companion to toString()
  /* Function to display Pile
   * Declared abstract to be defined in inherited classes
   */
  virtual void display() const = 0;  // for live game play, must override
  /* Function to get top Card from Pile
   * @return top Card in Pile
   */
  Card top();
  /* Function to insert Card at the bottom of a Pile
   * @param c Card to insert at bottom of Pile
   */
  void insert(Card& c);
};


#endif
