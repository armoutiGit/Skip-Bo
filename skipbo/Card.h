#ifndef _CARD_H
#define _CARD_H


class Card {
 public:
 Card(): value(0) { }
 Card(int v) { value = v >= 0 && v <= 12 ? v : 0; }
 ~Card() {}
 int getValue() const { return value; }
 std::string toString() const;  // for printing/file saving
 void display() const;   // live game play

 private:
 friend class Pile;
 int value;  // 0 for skip-bo card
};

#endif
