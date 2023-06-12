#ifndef __CHAMBER_H__
#define __CHAMBER_H__

#include "potion.h"
#include "treasure.h"
#include "enemy.h"
#include "position.h"
#include "seed.h"
#include <vector>

struct Position;

class Chamber {
  protected:
    std::vector<Position> cposition; // store all positions in chamber
    int size; // total size of chamber

  public:
    Chamber();
    Position randomPosition();
    void addPosition (Position pos);
    void addSize();
    ~Chamber();
  
    friend class Floor;
    friend class Game;
};

#endif
