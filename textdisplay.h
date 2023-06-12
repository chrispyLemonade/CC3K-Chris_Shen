#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include "observer.h"
#include "position.h"
#include "cell.h"

class Floor;

class TextDisplay: public Observer {
  std::vector<std::vector<char>> theFloor;
  const int row = 25;
  const int col = 79;

 public:
  // the normal constructor
  TextDisplay(int row, int col);

  void notify(Subject &whoNotified, CellType ctype, Position pos) override;

  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
