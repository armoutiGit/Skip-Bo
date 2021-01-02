#include <iostream>
#include "Hand.h"

Hand::Hand() {
  /*
  for (int i = 0; i < 5; i++) {
    pile[i] = nullptr;
  }*/
  handSize = 0;
}

Hand::~Hand() {
  
}

bool Hand::isEmpty() {
  return handSize == 0;
}

bool Hand::isFull() {
  return handSize == 5;
}

Card Hand::getCard(int idx) {
  return pile[idx];
}

int Hand::size() const {
  return handSize;
}

bool Hand::addCard(Card& card) {
  if (isFull()) {
    return false;
  }
  int i = 0;
  while (i < handSize) {
    i++;
  }
  pile[i] = card;
  handSize += 1;
  return true;
}

void Hand::popCard(int idx) {
  Card card(pile[idx].getValue());

  int i;
  for (i = idx; i < size(); i++) {
    pile[i] = pile[i + 1];
  }
  handSize -= 1;
}

// for live game play - must not change!
void Hand::display() const {
  int i;
  for (i = 0; i < size(); i++) {
    pile[i].display();
    std::cout << "  ";
  }
  for ( ; i < 5; i++)
    std::cout << "--  ";
}

std::string Hand::toString() const {
  std::string result;

  result.append(std::to_string(size()));
  result.append("\n");

  int i;
  for (i = 0; i < handSize; i++) {
    result.append(pile[i].toString());
    if (i < handSize - 1) {
      result.append(" ");
    }
  }
  
  result.append("\n");
  return result;
}

void Hand::readIn(std::istream* gameStream) {
  std::string thisIsAHand;
  int val;
  
  *gameStream >> thisIsAHand >> handSize;

  for (int i = 0; i < handSize; i++) {
    *gameStream >> val;
    Card c(val);
    pile[i] = c;
  }

}