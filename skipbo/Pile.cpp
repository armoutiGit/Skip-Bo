#include <vector>
#include "Pile.h"

bool Pile::isEmpty() {
  return pile.size() == 0;
}

void Pile::popCard() {
  
  pile.pop_back();
  return;
}

// for saving game state - must not change!
std::string Pile::toString() const {
  std::string result;
  result.append(std::to_string(size()));
  result.append("\n");
  // add all the pile elements to the string, at most 20 per line
  for (int i=0; i < size(); ++i) {
    if ((i % 20 == 0) && (i != 0))
      result.append("\n");
    else if (i != 0)
      result.append(" ");
    result.append(pile[i].toString());
  }
  result.append("\n");
  return result;
}

void Pile::readIn(std::istream* gameStream) {
  std::string pileType;
  int cap;
  int val;
  
  *gameStream >> pileType >> cap;
  
  for (int i = 0; i < cap; i++) {
    *gameStream >> val;
    Card card(val);
    addCard(card);
  } 
}

Card Pile::top() {
  return pile.back();
}

void Pile::insert(Card& c) {
  pile.insert(pile.begin(), c);
}