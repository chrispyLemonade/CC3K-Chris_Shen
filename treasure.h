#ifndef __TREASURE_H__
#define __TREASURE_H__

#include "thing.h"
#include "position.h"

class Treasure : public Thing {
    int value;
  public:
  // normal constructor
  Treasure(Position pos, CellType cType, int value);
  int getGold() override;
  virtual ~Treasure() = 0; // to make it be abstract class
};

class Shorde : public Treasure {
  public:
    Shorde(Position pos);
};

class Mhorde : public Treasure {
  public:
    Mhorde(Position pos);
};

class Compass : public Treasure {
  public:
    Compass(Position pos, int value);
    CellType getCType() override;
};

class Nhorde : public Treasure {
  public:
    Nhorde(Position pos);
};



// the dragon horde
class Dhorde : public Treasure {
  protected:
    bool hasDragon;
  public:
    Dhorde(Position pos, CellType cType, int value);
    bool getHasDragon() override;
    void dragonDead() override;
};

class BarrierSuit : public Dhorde {
  public:
    BarrierSuit(Position pos, int value);
    CellType getCType() override;
};


#endif
