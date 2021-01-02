#ifndef DRAW_PILE_H
#define DRAW_PILE_H

#include "Pile.h"

class DrawPile : public Pile {

    public:
    DrawPile();
    virtual ~DrawPile();
    void display() const;
    std::string getRand() const;

    void DeckToDraw(std::istream& stream);

    void shuffle();

    std::string shuffled;
};

#endif