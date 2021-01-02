#include <iostream>
#include <vector>

#include "DrawPile.h"

DrawPile::DrawPile() { }

DrawPile::~DrawPile() { }

// for live game play - must not change!
void DrawPile::display() const {
  std::cout << "[XX]/" << size();
}


std::string DrawPile::getRand() const {
  return shuffled;
}

void DrawPile::DeckToDraw(std::istream& stream) {
  int val;
  while (stream >> val) {
    Card card(val);
    addCard(card);
  }
}

void DrawPile::shuffle() {
  std::random_shuffle(pile.begin(), pile.end());
}