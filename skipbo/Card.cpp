#include <iostream>
#include <string>
#include "Card.h"

// for live game play - must not change!
void Card::display() const {
  std::cout << "[";
  if (value == 0) 
    std::cout << "SB";
  else {
    std::cout << value;
  }
  std::cout << "]";
 }

// for saving game state - must not change!
std::string Card::toString() const { 
  return std::to_string(value);
 }

