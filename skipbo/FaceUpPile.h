#ifndef FACEUP_PILE_H
#define FACEUP_PILE_H

#include "Pile.h"

class FaceUpPile : public Pile {

    public:
    FaceUpPile() {}
    virtual ~FaceUpPile();
    void display() const;

};

#endif