#ifndef _DECORATOR_H_
#define _DECORATOR_H_

#include "player.h"

class Decorator : public Player {
protected:
  Player *component;

public:
  Decorator(Position pos, CellType cType, int HP, int Atk, int Def, Player *component);
  virtual ~Decorator();
};

#endif
