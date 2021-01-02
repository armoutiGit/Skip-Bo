#include <iostream>
#include "BuildPile.h"

//Destructor for BuildPile
BuildPile::~BuildPile() {
  while (!isEmpty()) {
    pile.pop_back();
  }
}
