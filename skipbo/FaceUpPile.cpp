#include <iostream>
#include "FaceUpPile.h"

FaceUpPile::~FaceUpPile() {
  while (!isEmpty()) {
    pile.pop_back();
  }
}

// for live game play - must not change!
void FaceUpPile::display() const {
  if (size()) {
    pile[pile.size()-1].display();
  }
  else std::cout << "--";
  std::cout << "/" << size();
}


